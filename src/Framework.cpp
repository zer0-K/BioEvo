#include "Framework.hpp"

#include "Declaration/PreprocessingDefinitions.hpp"
#include "Declaration/Constants.hpp"
#include "Utils/Log/Logger.hpp"

#include <iostream>

Framework::Framework()
{
    this->nb_universes = 0;
    this->nb_max_solutions = DEFAULT_NB_MAX_SOLUTIONS;
    this->current_nb_solutions = 0;
}

Framework::Framework(int nb_universes, Universe** universes)
    :Framework::Framework(nb_universes, universes, DEFAULT_NB_MAX_SOLUTIONS)
{
    // nothing here
}

Framework::Framework(int nb_universes, Universe** universes, int nb_max_solutions)
{
    this->nb_universes = nb_universes;
    this->universes = universes;
    this->nb_max_solutions = nb_max_solutions;
    this->current_nb_solutions = 0;
}

void Framework::init()
{
    for(int i=0; i<this->nb_universes;i++)
    {
        this->universes[i]->init();
    }
}

void Framework::insert_solution(Solution* evolved_solution)
{
    Solution* current_solution;

    // for the moment, insert sort
    for(int i=this->current_nb_solutions-1; i>=0; i--)
    {

        current_solution = this->evolved_solutions[i];

        if(evolved_solution->is_better(current_solution))
        {
            // if our model is better, downgrade current solution
            if(i==this->nb_max_solutions)
            {
                delete current_solution;
            }
            else
            {
                this->evolved_solutions[i+1] = current_solution;
            }
        } 
        else
        {
            // our solution is worse than current one, downgrade new solution
            if(i==this->nb_max_solutions)
            {
#if LOG_LEVEL > 0
                //std::string log_text = "New evolved solution is worse than all evolved solutions already found";
                //std::string flags[] = { FLAG_INFO };
                //logger_write(flags, 1, log_text);
#endif
                delete evolved_solution;
            }
            else
            {
#if LOG_LEVEL > 0
                //std::string log_text = "New evolved solution is inserted at rank " + std::to_string(i);
                //std::string flags[] = { FLAG_INFO };
                //logger_write(flags, 1, log_text);
#endif
                this->evolved_solutions[i+1] = evolved_solution;

                if(this->current_nb_solutions<this->nb_max_solutions)
                {
                    this->current_nb_solutions = this->current_nb_solutions+1;
                }
            }
            // no need to continue loop, we have inserted our new solution
            break;
        }
    }

    if(this->current_nb_solutions==0)
    {
        this->evolved_solutions[0] = evolved_solution;
    }
}

void Framework::next_step_environment(int universe_index)
{
   this->universes[universe_index]->next_step_environment();
}

void Framework::next_step_individual(int universe_index, int individual_index)
{
    this->universes[universe_index]->next_step_individual(individual_index);
}

void Framework::next_step_individuals(int universe_index)
{
    this->universes[universe_index]->next_step_individuals();

}

void Framework::next_step(int universe_index)
{
    this->universes[universe_index]->next_step();
}

void Framework::test(int universe_index, int nb_vals)
{
    logger_write(0, FLAG_INFO + FLAG_FRAMEWORK + FLAG_BEGIN + "Test");

    Universe* universe = this->universes[universe_index];

    // create some inputs for the individuals 
    std::vector<sp_flow> prepared_vals = universe->prepare_values(nb_vals);

    // adapt the values for the individuals
    std::vector<sp_flow> computed_vals = universe->individuals_compute(prepared_vals);

    Solution** solutions = new Solution*[universe->get_nb_individuals()];
    double* gaps = universe->compute_errors(prepared_vals, computed_vals, universe->get_nb_individuals());
    for(int i=0; i<universe->get_nb_individuals();i++)
    {
        solutions[i] = new Solution(universe->get_individuals()[i], gaps[i]);
    }

    logger_write(0, FLAG_INFO + FLAG_FRAMEWORK + FLAG_END + "Test");
}


//---------- setters

void Framework::set_universes(int nb_universes, Universe** universes)
{
    this->nb_universes = nb_universes;
    this->universes = universes;
}

void Framework::add_universe(Universe* universe)
{
    // check if the universe already exists or not first
    bool isin = false;
    for(int i=0;i<this->nb_universes;i++)
    {
        if(this->universes[i]->get_name() == universe->get_name())
        {
            isin = true;
            break;
        }
    }

    if(!isin)
    {
        Universe** universes_old = this->universes;
        this->universes = new Universe*[this->nb_universes+1];

        for(int i=0; i<this->nb_universes;i++)
        {
            this->universes[i] = universes_old[i];
        }
        this->universes[this->nb_universes] = universe;

        this->nb_universes++;
    }
}

void Framework::set_environment(Environment* env, int universe_nb)
{
    this->universes[universe_nb]->set_environment(env);
}

void Framework::set_environment(Environment* env, std::string universe_name)
{
    for(int i=0; i<this->nb_universes;i++)
    {
        if( this->universes[i]->get_name().compare(universe_name)==0 )
        {
            this->set_environment(env, i);
            break;
        }
    }
}
    
void Framework::set_individuals(Individual** individuals, int nb_individuals, int universe_nb)
{
    if(universe_nb<this->nb_universes)
    {
        this->universes[universe_nb]->set_individuals(individuals, nb_individuals);
    }
}

void Framework::set_individuals(Individual** individuals, int nb_individuals, std::string universe_name)
{
    for(int i=0; i<this->nb_universes;i++)
    {
        if( this->universes[i]->get_name() == universe_name )
        {
            this->set_individuals(individuals, nb_individuals, i);
            break;
        }
    }
}


//---------- other

std::string Framework::to_string()
{
    std::string res = "";

    for(int i=0;i<this->nb_universes;i++)
    {
        res += this->universes[i]->get_name() + " : " + this->universes[i]->to_string();
    }

    return res;
}

boost::json::object Framework::to_json()
{
    boost::json::object jframework;

    boost::json::object juniv;
    for(int i=0; i<this->nb_universes;i++)
        juniv[this->universes[i]->get_name()] = this->universes[i]->to_json();
    jframework["universes"] = juniv;

    return jframework;
}