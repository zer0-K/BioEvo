#include "experiment_1.hpp"

#include <fstream>
#include <chrono>
#include <thread>
#include "../Declaration/PreprocessingDefinitions.hpp"
#include "../Utils/Log/Logger.hpp"
#include "../Utils/Math/RandomGen.hpp"
#include "../Declaration/Constants.hpp"
#include "../Flow/Buffer/BufferLinear.hpp"
#include "../Environment/EnvironmentLinear.hpp"
#include "../Individual/IndividualLinear.hpp"


//---------- constants

const int NB_SUFFIXES_EXPERIMENT_1 = 2;

std::string LOG_SUFFIXES_EXPERIMENT_1[NB_SUFFIXES_EXPERIMENT_1] = {
    EXPERIMENT_CLASSICAL_ALGO_SUFFIX,
    "1"
};

//---------- functions

int experiment_1()
{
    logger_init(LOG_SUFFIXES_EXPERIMENT_1, NB_SUFFIXES_EXPERIMENT_1, EXPERIMENT_CLASSICAL_ALGO_1);
    logger_write(0, FLAG_INIT + "Beginning of experiment 1");

    int experiment_result = 0;
    Framework* framework_experiment_1 = new Framework();

    experiment_result = experiment_1_1(framework_experiment_1);
    //experiment_result = experiment_1_2(framework_experiment_1, 1);

    logger_write(0, FLAG_INIT + "End of experiment 1");
    logger_end();

    return experiment_result;
}

//-------------------- Experiment 1.1

int experiment_1_1(Framework* framework)
{
    logger_write(0, FLAG_INIT + "Beginning of experiment 1.1");

    //---------- Creating environment

    // params
    std::string env_name = "environment linear model 1";
    int dim = 4;
    double w[] = { 3, -33, 0, 100 };
    double b = 0;

    // environment
    EnvironmentLinear* env_linear = new EnvironmentLinear(env_name, dim, w, b);
    logger_write(2, FLAG_INFO + FLAG_DETAILS + env_linear->to_string());


    //---------- Creating individuals

    // params
    int nb_individuals = 1;
    std::string name_individuals[] = { "individual 1"};
    int nb_epochs[] = { 100 };

    // individuals
    Individual* individuals[nb_individuals];
    for(int i=0; i<nb_individuals;i++)
    {
        individuals[i] = (Individual*) new IndividualLinear(name_individuals[i], nb_epochs[i], 4);
    }


    //----- Creating buffer

    BufferLinear* buffer_linear = new BufferLinear();


    //---------- Creating universe

    std::string name_universe = "universe experiment 1.1";
    Universe* universe = new Universe(name_universe, individuals, nb_individuals, (Environment*) env_linear, (Buffer*) buffer_linear); 


    //---------- Creating framework

    int nb_universes = 1;
    Universe* universes[] = { universe };
    framework->set_universes(nb_universes, universes);



    //---------- Experiment begins here ----------
    
    auto t1 = std::chrono::high_resolution_clock::now();
    int universe_index = 0;
    framework->init();
    framework->next_step(universe_index);

    // time stuff
    auto t2 = std::chrono::high_resolution_clock::now();
    auto exec_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout<<"Exec time of one step : "<<exec_duration.count()<<std::endl;

    framework->test(0, 10);

    logger_write(0, FLAG_INFO + "End of experiment 1.1");

    return 0;
}

//-------------------- Experiment 1.2

int experiment_1_2(Framework* framework, int dim)
{
    logger_write(0, FLAG_INIT + "Beginning of experiment 1.2");

    //---------- Hyper parameters

    int rand_bound = 20;

    //---------- Creating environment

    // params
    std::string env_name = "environment linear model 2";
    double* w = new double[dim];
    for(int d=0;d<dim;d++)
    {
        w[d] = rand_gen::rand_double(-rand_bound,rand_bound);
    }
    double b = rand_gen::rand_double(-rand_bound, rand_bound);

    // environment
    EnvironmentLinear* env_linear = new EnvironmentLinear(env_name, dim, w, b);


    //---------- Creating individuals

    // params
    int nb_individuals = 1;
    std::string name_individuals[] = { "individual 1"};
    int nb_epochs[] = { 100 };

    // individuals
    Individual* individuals[nb_individuals];
    for(int i=0; i<nb_individuals;i++)
    {
        individuals[i] = (Individual*) new IndividualLinear(name_individuals[i], nb_epochs[i]);
    }


    //----- Creating buffer

    BufferLinear* buffer_linear = new BufferLinear();


    //---------- Creating universe

    std::string name_universe = "universe experiment 1.1";
    Universe* universe = new Universe(name_universe, individuals, nb_individuals, (Environment*) env_linear, (Buffer*) buffer_linear);
    universe->show();


    //---------- Creating framework

    int nb_universes = 1;
    Universe* universes[] = { universe };
    framework->set_universes(nb_universes, universes);



    //---------- Experiment begins here ----------
    
    auto t1 = std::chrono::high_resolution_clock::now();
    int universe_index = 0;
    framework->next_step(universe_index);

    // time stuff
    auto t2 = std::chrono::high_resolution_clock::now();
    auto exec_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout<<"Exec time of one step : "<<exec_duration.count()<<std::endl;

    logger_write(0, FLAG_INFO + "End of experiment 1.1");

    return 0;
}
double lower_bound = 0;
    double upper_bound = 10000;
