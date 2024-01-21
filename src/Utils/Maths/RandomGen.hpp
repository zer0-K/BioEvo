#pragma once

#include <random>

/**
 * @brief Random generator (singleton) for different laws
*/
class rand_gen
{
public:
    std::default_random_engine generator;
    std::normal_distribution<double> normal;
    std::geometric_distribution<int> geom;
    static rand_gen* rg;

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
            rg = new rand_gen();

        std::uniform_real_distribution<double> unif(low_bound,up_bound);
        double random_double = unif(rg->generator);
     
        return random_double;
    }

    static int rand_int(int low_bound, int up_bound)
    {
        if(rg == NULL)
            rg = new rand_gen();

        int random_int = rand()%(up_bound-low_bound + 1) + low_bound;     
        return random_int;
    }

    static double rand_normal(double mean, double std_dev)
    {
        if(rg == NULL)
            rg = new rand_gen();

        double random_double = rg->normal(((rand_gen*)rg)->generator);
        return mean + std_dev * random_double;
    }

    // generate an integer for geometric distribution with param p=a/b
    static int rand_geom(int a, int b)
    {
        if(rg == NULL)
            rg = new rand_gen();

        double p = ((double) a) / ((double) b);
        rg->geom = std::geometric_distribution<int>(p);

        int rand_nb = rg->geom(((rand_gen*)rg)->generator);
        return rand_nb;
    }
    
    // generate an integer for geometric distribution with param p
    static int rand_geom(double p)
    {
        if(rg == NULL)
            rg = new rand_gen();

        rg->geom = std::geometric_distribution<int>(p);

        int rand_nb = rg->geom(((rand_gen*)rg)->generator);
        return rand_nb;
    }
};

inline rand_gen* rand_gen::rg = NULL;