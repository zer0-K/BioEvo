#pragma once

#include <random>

class rand_gen
{
public:
    std::default_random_engine generator;
    std::normal_distribution<double> normal;
    static void* rg;

private:

    rand_gen()
    {
        generator = std::default_random_engine();
        normal = std::normal_distribution(0.0, 1.0);
    }

public:
    static double rand_double(int low_bound, int up_bound)
    {
        if(rg == NULL)
            rg = (void*) new rand_gen();

        std::uniform_real_distribution<double> unif(low_bound,up_bound);
        double random_double = unif(((rand_gen*)rg)->generator);
     
        return random_double;
    }

    static double rand_normal(double mean, double std_dev)
    {
        if(rg == NULL)
            rg = (void*) new rand_gen();

        double random_double = ((rand_gen*)rg)->normal(((rand_gen*)rg)->generator);
        return mean + std_dev * random_double;
    }
};