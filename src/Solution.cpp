#include "Solution.hpp"

Solution::Solution(Individual* evolved_solution, float gap)
{
    this->evolved_solution = evolved_solution;
    this->gap = gap;
}

Individual* Solution::get_evolved_solution()
{
    return this->evolved_solution;
}

bool Solution::is_better(Solution* comp_solution)
{
    return this->gap < comp_solution->get_gap();
}


float Solution::get_gap()
{
    return this->gap;
}