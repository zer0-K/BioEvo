#include "Framework.hpp"

#include "Declaration/PreprocessingDefinitions.hpp"
#include "Declaration/Constants.hpp"
#include "Utils/Log/Logger.hpp"

#include <iostream>

Framework::Framework()
{
    nb_universes = 0;
    nb_max_solutions = DEFAULT_NB_MAX_SOLUTIONS;
    current_nb_solutions = 0;
}

Framework::Framework(std::vector<sp_universe> universes)
    :Framework::Framework(universes, DEFAULT_NB_MAX_SOLUTIONS)
{
    // nothing here
}

Framework::Framework(std::vector<sp_universe> universes, int nb_max_solutions)
{
    this->nb_universes = nb_universes;
    this->universes = universes;
    this->nb_max_solutions = nb_max_solutions;
    this->current_nb_solutions = 0;
}


std::string Framework::launch(std::string universe_name, int nb_steps)
{
    std::string ready_message = is_ready(universe_name);
    if(ready_message != "ready")
    {
        return ready_message;
    }

    int pos = get_universe_pos(universe_name); 

    for(int step=0; step<nb_steps;step++)
    {
        next_step(pos);
    }
    
    return "Success";
}


void Framework::insert_solution(Solution* evolved_solution)
{
    Solution* current_solution;

    // for the moment, insert sort
    for(int i=current_nb_solutions-1; i>=0; i--)
    {

        current_solution = evolved_solutions[i];

        if(evolved_solution->is_better(current_solution))
        {
            if(i!=nb_max_solutions)
            {
                evolved_solutions[i+1] = current_solution;
            }
        } 
        else
        {
            if(i!=nb_max_solutions)
            {
                evolved_solutions[i+1] = evolved_solution;

                if(current_nb_solutions<nb_max_solutions)
                {
                    current_nb_solutions = current_nb_solutions+1;
                }
            }
            // no need to continue loop, we have inserted our new solution
            break;
        }
    }

    if(current_nb_solutions==0)
    {
        evolved_solutions[0] = evolved_solution;
    }
}

void Framework::next_step(int universe_index)
{
    universes[universe_index]->next_step();
}

void Framework::test(int universe_index, int nb_vals)
{
    logger_write(0, FLAG_INFO + FLAG_FRAMEWORK + FLAG_BEGIN + "Test");

    sp_universe universe = universes[universe_index];

    Solution** solutions = new Solution*[universe->get_nb_individuals()];
    //std::vector<double> gaps = universe->compute_errors(universe->get_nb_individuals());
    for(int i=0; i<universe->get_nb_individuals();i++)
    {
        //solutions[i] = new Solution(universe->get_individuals()[i], gaps[i]);
    }

    logger_write(0, FLAG_INFO + FLAG_FRAMEWORK + FLAG_END + "Test");
}


//---------- setters

void Framework::set_universes(std::vector<sp_universe> universes)
{
    this->nb_universes = nb_universes;
    this->universes = universes;
}

void Framework::add_universe(sp_universe universe)
{
    // add universe only if it does not already exist
    if(get_universe_pos(universe->get_name()) == -1)
    {
        universes.push_back(universe);
        nb_universes++;
    }
}

void Framework::set_environment(sp_environment env, int universe_nb)
{
    universes[universe_nb]->set_environment(env);
}

void Framework::set_environment(sp_environment env, std::string universe_name)
{
    for(int i=0; i<nb_universes;i++)
    {
        if( universes[i]->get_name().compare(universe_name)==0 )
        {
            set_environment(env, i);
            break;
        }
    }
}
    
void Framework::set_individuals(std::vector<sp_individual> individuals, int universe_nb)
{
    if(universe_nb<nb_universes)
    {
        universes[universe_nb]->set_individuals(individuals);
    }
}

void Framework::set_individuals(std::vector<sp_individual> individuals, std::string universe_name)
{
    for(int i=0; i<nb_universes;i++)
    {
        if( universes[i]->get_name() == universe_name )
        {
            set_individuals(individuals, i);
            break;
        }
    }
}

void Framework::add_individual(sp_individual individual, std::string universe_name)
{
    int pos = get_universe_pos(universe_name);

    if(pos != -1)
    {
        universes[pos]->add_individual(individual);
    }
}


//---------- getters

int Framework::get_universe_pos(std::string universe_name)
{
    for(int i=0;i<universes.size();i++)
    {
        if(universes[i]->get_name() == universe_name)
        {
            return i;
        }
    }

    return -1;
}

sp_environment Framework::get_environment(std::string universe_name)
{
    int pos = get_universe_pos(universe_name);

    if(pos == -1)
        return nullptr;

    return universes[pos]->get_environment();
}

//---------- other

std::string Framework::to_string()
{
    std::string res = "";

    for(int i=0;i<nb_universes;i++)
    {
        res += universes[i]->get_name() + " : " + universes[i]->to_string();
    }

    return res;
}

boost::json::object Framework::to_json()
{
    boost::json::object jframework;

    boost::json::object juniv;
    for(int i=0; i<nb_universes;i++)
        juniv[universes[i]->get_name()] = universes[i]->to_json();
    jframework["universes"] = juniv;

    return jframework;
}

std::string Framework::is_ready(std::string universe_name)
{
    int univ_pos = get_universe_pos(universe_name);

    if(univ_pos != -1)
    {
        std::string message = universes[univ_pos]->is_ready();

        if(message == "ready")
        {
            return "ready";
        }
        else
        {
            return message;
        }
    }
    else
    {
        return "No universe with given name : " + universe_name;
    }
}