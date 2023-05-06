#pragma once

#include "Individual/Individual.hpp"

/// @brief evolutionary solutions of an optimisation
class Solution
{
private:
    std::string name;   ///< name of the solution
    Individual* evolved_solution; ///< algorithm which encodes the solution we found
    double error;  ///< difference between the solution we found and the real solution

public:
    /**
     * @brief Constructor
     * 
     * @param[in] evolved_solution individual which has evolved to be close to the solution
     * @param[in] gap difference between the evolved solution and the real solution
    */
    Solution(Individual* evolved_solution, double gap);

    /**
     * @brief tells if the current solution is better than the given one
     * 
     * @param[in] comp_solution evolved solution to compare with current one
     * 
     * @return true if current solution is better
    */
    bool is_better(Solution* solution);


    //----- getters
    Individual* get_evolved_solution();
    double get_error(); 

    //----- other
    std::string to_string();
};