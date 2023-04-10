#include "experiment_classical_algo_1.hpp"

#include <fstream>
#include "../../Utils/Log/Logger.hpp"
#include "../../Constants.hpp"
#include "../../Buffer.hpp"
#include "../../ClassicalAlgos/ClassicalUniverse.hpp"
#include "../../ClassicalAlgos/LinearRegression/BufferLinear.hpp"
#include "../../ClassicalAlgos/LinearRegression/EnvironmentLinear.hpp"
#include "../../ClassicalAlgos/LinearRegression/Individuals/LinearRegressionIndividual.hpp"


//---------- constants

const int NB_SUFFIXES_EXPERIMENT_1 = 2;

std::string LOG_SUFFIXES_EXPERIMENT_1[NB_SUFFIXES_EXPERIMENT_1] = {
    EXPERIMENT_CLASSICAL_ALGO_SUFFIX,
    "1"
};

//---------- functions

int experiment_1()
{
    int experiment_result = 0;
    Framework* framework_experiment_1 = new Framework();

#if LOG
    logger_init(
        LOG_SUFFIXES_EXPERIMENT_1, 
        NB_SUFFIXES_EXPERIMENT_1, 
        EXPERIMENT_CLASSICAL_ALGO_1); 
#endif

#if DEBUG || VERBOSE
    std::cout<<"---------- Beginning of experiment 1"<<std::endl;
#endif

    experiment_result = experiment_1_1(framework_experiment_1);

#if DEBUG
    std::cout<<"---------- End of experiment 1"<<std::endl;
#endif

#if LOG
    logger_end();
#endif

    return experiment_result;
}

int experiment_1_1(Framework* framework)
{
#if DEBUG
    std::cout<<"---------- Experiment 1.1"<<std::endl;
#endif

#if LOG
    std::string text_create_env = "Creating environment...";
    std::string flags_create_env[] = { FLAG_INIT };
    logger_write(flags_create_env, 1, text_create_env);
#endif

    std::string name_env = "Environment linear model";
    int dimension = 1;
    double w[] = { 3 };
    double b = 5;
    EnvironmentLinear* env_linear = new EnvironmentLinear(name_env, dimension, w, b);

    int nb_individuals = 1;
    std::string name_individuals[] = {
        "Individual 1"
    };
    Individual* individuals[nb_individuals];
    for(int i=0; i<nb_individuals;i++)
    {
        individuals[i] = (Individual*) new LinearRegressionIndividual(name_individuals[i]);
    }

    BufferLinear* buffer_linear = new BufferLinear();

    std::string name_universe = "Universe experiment 1";
    Universe* universe = new Universe(name_universe, individuals, nb_individuals, (Environment*) env_linear, (Buffer*) buffer_linear);
    universe->show();

#if LOG
    std::string text_env_created = "...environment created";
    std::string flags_env_created[] = { FLAG_INIT };
    logger_write(flags_env_created, 1, text_env_created);
#endif

    int nb_universes = 1;
    Universe* universes[] = { universe };
    framework->set_universes(nb_universes, universes);

#if DEBUG
    std::cout<<"---------- End of experiment 1.1"<<std::endl;
#endif
    return 0;
}
