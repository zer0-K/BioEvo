#include "Solution.hpp"

Solution::Solution(Individual* evolved_solution, double error)
{
    this->evolved_solution = evolved_solution;
    this->error = error;
}

Individual* Solution::get_evolved_solution()
{
    return this->evolved_solution;
}

bool Solution::is_better(Solution* comp_solution)
{
    return this->error < comp_solution->get_error();
}


double Solution::get_error()
{
    return this->error;
}

std::string Solution::to_string()
{
    std::string res = "";

    res += name + std::to_string(error) + " for " + this->evolved_solution->to_string();

    return res;
}