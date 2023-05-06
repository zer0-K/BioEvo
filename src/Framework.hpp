#pragma once

#include "Universe.hpp"
#include "Solution.hpp"

class Framework
{
private:
    int nb_universes;   ///< number of universes
    std::vector<sp_universe> universes;   ///< universes in which

    Solution** evolved_solutions;   ///< evolved solutions (sorted : first element is best solution)
    int nb_max_solutions;   ///< max number of evolved solutions we want to keep
    int current_nb_solutions;   ///< current number of found solutions

public:
    /**
     * @brief Constructor
    */
    Framework();

    /**
     * @brief Constructor
     * 
     * @param[in] universes universes
    */
    Framework(std::vector<sp_universe> universes);

    /**
     * @brief Constructor
     * 
     * @param[in] universes universes
     * @param[in] nb_max_solutions max number of solutions we want to keep
    */
    Framework(std::vector<sp_universe> universes, int nb_max_solutions);

    

    /**
     * @brief Initialize everything so that the first step is smooth
    */
    void init();

    /**
     * @brief perform one environment step
     * 
     * @param[in] universe_index index of the universe
    */
    void next_step_environment(int universe_index);

    /**
     * @brief perform one step for the given individual
     * 
     * @param[in] individual_index index of the individual in the array of individuals
     * @param[in] universe_index index of the universe
    */
    void next_step_individual(int universe_index, int individual_nb);

    /**
     * @brief perform on step for all the individuals
     * 
     * @param[in] universe_index index of the universe
    */
    void next_step_individuals(int universe_index);

    /**
     * @brief Perform one step
     * 
     * @param[in] universe_index index of the universe
    */
    void next_step(int universe_index);
    
    /**
     * @brief Insert a new solution into our evolved solutions
     * 
     * @param[in] evolved_solution evolved solution to insert
    */
    void insert_solution(Solution* evolved_solution);

    /**
     * @brief Test the individuals of the given universe
     * 
     * @param[in] universe_index index of the universe to test
     * @param[in] nb_vals number of values for the test
    */
    void test(int universe_index, int nb_vals);

    
    //----- setters
    void set_universes(std::vector<sp_universe> universes);
    void add_universe(sp_universe universe);
    void set_environment(sp_environment env, int universe_nb);
    void set_environment(sp_environment env, std::string universe_name);
    void set_individuals(std::vector<sp_individual> individuals, int universe_nb);
    void set_individuals(std::vector<sp_individual> individuals, std::string universe_name);

    //----- other
    std::string to_string();
    boost::json::object to_json();
};

typedef std::shared_ptr<Framework> sp_framework;