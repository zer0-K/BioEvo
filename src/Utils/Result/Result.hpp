#pragma once

#include "../../Solution.hpp"

/// @brief Experiment result
class Result
{
protected:
    int nb_solutions;   ///< number of solutions
    Solution** solutions;   ///< solutions
    double* test_errors;    ///< errors of the solutions

public:

    //----- setters
    void set_solutions(Solution** solutions, int nb_solutions);

    //----- other
    std::string to_string();
};