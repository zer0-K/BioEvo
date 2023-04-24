#include "Framework.hpp"

#include "PreprocessingDefinitions.hpp"
#include "Constants.hpp"
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

void Framework::test(Result* result, int universe_index, int nb_vals)
{
    logger_write(0, FLAG_INFO + FLAG_FRAMEWORK + FLAG_BEGIN + "Test");

    Universe* universe = this->universes[universe_index];

    // create some inputs for the individuals 
    Flow** prepared_vals = universe->prepare_values(nb_vals);

    // adapt the values for the individuals
    Flow** computed_vals = universe->individuals_compute(prepared_vals);

    Solution** solutions = new Solution*[universe->get_nb_individuals()];
    double* gaps = universe->compute_errors(prepared_vals, computed_vals, universe->get_nb_individuals());
    for(int i=0; i<universe->get_nb_individuals();i++)
    {
        solutions[i] = new Solution(universe->get_individuals()[i], gaps[i]);
    }

    result->set_solutions(solutions, universe->get_nb_individuals());

    logger_write(0, FLAG_INFO + FLAG_FRAMEWORK + FLAG_END + "Test");
}

//---------- setters

void Framework::set_universes(int nb_universes, Universe** universes)
{
    this->nb_universes = nb_universes;
    this->universes = universes;
}

//---------- other

std::string Framework::to_string()
{
    std::string res = "";

    res += "";

    return res;
}