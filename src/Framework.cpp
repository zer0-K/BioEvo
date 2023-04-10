#include "Framework.hpp"

#include "Constants.hpp"
#include "Utils/Log/Logger.hpp"

Framework::Framework()
{
    this->nb_universes = 0;
    this->nb_max_solutions = DEFAULT_NB_MAX_SOLUTIONS;
    this->current_nb_solutions = 0;
}

Framework::Framework(int nb_universes, Universe** universes)
    :Framework::Framework(nb_universes, universes, DEFAULT_NB_MAX_SOLUTIONS)
{
}

Framework::Framework(int nb_universes, Universe** universes, int nb_max_solutions)
{
    this->nb_universes = nb_universes;
    this->universes = universes;
    this->nb_max_solutions = nb_max_solutions;
    this->current_nb_solutions = 0;
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
#if LOG
                std::string log_text = "New evolved solution is worse than all evolved solutions already found";
                std::string flags[] = { FLAG_INFO };
                logger_write(flags, 1, log_text);
#endif
                delete evolved_solution;
            }
            else
            {
#if LOG
                std::string log_text = "New evolved solution is inserted at rank " + std::to_string(i);
                std::string flags[] = { FLAG_INFO };
                logger_write(flags, 1, log_text);
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

void Framework::set_universes(int nb_universes, Universe** universes)
{
    delete this->universes;

    this->nb_universes = nb_universes;
    this->universes = universes;
}