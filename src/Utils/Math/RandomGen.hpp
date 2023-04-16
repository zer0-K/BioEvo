#pragma once

#include <random>

double rand_double(int low_bound, int up_bound);

double rand_double(int low_bound, int up_bound)
{
    std::uniform_real_distribution<double> unif(low_bound,up_bound);
    std::default_random_engine re;
    double random_double = unif(re);
     
    return random_double;
}