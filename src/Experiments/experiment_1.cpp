#include "experiment_1.hpp"

#include <fstream>
#include <chrono>
#include <thread>
#include "../Declaration/PreprocessingDefinitions.hpp"
#include "../Utils/Log/Logger.hpp"
#include "../Utils/Math/RandomGen.hpp"
#include "../Declaration/Constants.hpp"
#include "../Environment/EnvironmentLinear.hpp"
#include "../Individual/IndividualLinear.hpp"


//---------- constants

double lower_bound = 0;
double upper_bound = 10000;

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
    sp_framework framework_experiment_1 = std::make_shared<Framework>();

    experiment_result = experiment_1_1(framework_experiment_1);
    //experiment_result = experiment_1_2(framework_experiment_1, 1);

    logger_write(0, FLAG_INIT + "End of experiment 1");
    logger_end();

    return experiment_result;
}

//-------------------- Experiment 1.1

int experiment_1_1(sp_framework framework)
{
    logger_write(0, FLAG_INIT + "Beginning of experiment 1.1");

    //---------- Creating environment

    // params
    std::string env_name = "environment linear model 1";
    int dim = 4;
    std::vector<double> w{ 3, -33, 0, 100 };
    double b = 0;

    size_t size_test = 80;
    size_t size_validation = 20;

    // environment
    sp_environment_linear env_linear = std::make_shared<EnvironmentLinear>(env_name, size_test, size_validation, dim, w, b);
    logger_write(2, FLAG_INFO + FLAG_DETAILS + env_linear->to_string());


    //---------- Creating individuals

    // params
    int nb_individuals = 1;
    std::string name_individuals[] = { "individual 1"};

    // individuals
    std::vector<sp_individual> individuals(nb_individuals);
    for(int i=0; i<nb_individuals;i++)
    {
        individuals[i] = std::make_shared<IndividualLinear>(name_individuals[i], 4);
    }


    //---------- Creating universe

    std::string name_universe = "universe experiment 1.1";
    sp_universe universe = std::make_shared<Universe>(name_universe, individuals, env_linear); 


    //---------- Creating framework

    int nb_universes = 1;
    std::vector<sp_universe> universes{ universe };
    framework->set_universes(universes);



    //---------- Experiment begins here ----------
    
    auto t1 = std::chrono::high_resolution_clock::now();
    int universe_index = 0;
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

int experiment_1_2(sp_framework framework, int dim)
{
}
