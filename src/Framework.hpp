#pragma once

#include "Universe.hpp"
#include "Solution.hpp"

class Framework
{
private:
    int nb_universes;   ///< number of universes
    Universe** universes;   ///< universes in which

    Solution** evolved_solutions;   ///< evolved solutions (sorted : first element is best solution)
    int nb_max_solutions;   ///< max number of evolved solutions we want to keep
    int current_nb_solutions;   ///< current number of found solutions

public:
    /**
     * Constructor
    */
    Framework();

    /**
     * Constructor
     * 
     * @param[in] nb_universes number of universes
     * @param[in] universes universes
    */
    Framework(int nb_universes, Universe** universes);

    /**
     * Constructor
     * 
     * @param[in] nb_universes number of universes
     * @param[in] universes universes
     * @param[in] nb_max_solutions max number of solutions we want to keep
    */
    Framework(int nb_universes, Universe** universes, int nb_max_solutions);

    /**
     * @brief insert a new solution into our evolved solutions
     * 
     * @param[in] evolved_solution evolved solution to insert
    */
    void insert_solution(Solution* evolved_solution);

    // setters
    void set_universes(int nb_universes, Universe** universes);
};