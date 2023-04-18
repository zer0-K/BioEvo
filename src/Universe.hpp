#pragma once

#include "PreprocessingDefinitions.hpp"
#include "Buffer.hpp"
#include <map>
#include <string>

/// @brief universe for the experiments
class Universe
{
protected:
    std::string name;   ///< name of the universe

    int width;  ///< width of the universe
    int height; ///< height of the universe

    int number_of_individuals;      ///< current number of individuals in the universe
    int max_number_of_individuals;  ///< maximum number of individuals in the universe
    int* epochs_individuals;    ///< number of epochs for the individuals

    Individual** individuals;   ///< individuals living in the universe
    Environment* environment;   ///< environment with which the individual interacts
    Buffer* buffer;             ///< buffer, to feed individual's input with environment's output and vice-vesra
        
    std::map<Individual*, double> solutions;     ///< solutions of the problem

    int t;  ///< time

    bool state; ///< universe state

public:

    /**
     * @brief Constructor
     * 
     * @param[in] name name of the universe
    */
    Universe(std::string name);
    
    /**
     * @brief Constructor
     * 
     * @param[in] width width of the universe
     * @param[in] height height of the universe
    */
    Universe(const int width, const int height);

    /**
     * @brief Constructor
     * 
     * @param[in] name name of the universe
     * @param[in] individuals individuals at beginning of the universe
     * @param[in] nb_individuals number of individuals
     * @param[in] environment environment
     * @param[in] buffer buffer
    */
    Universe(std::string name, Individual** individuals, int nb_individuals, Environment* environment, Buffer* buffer);

     /**
     * @brief Constructor
     * 
     * @param[in] name name of the universe
     * @param[in] individuals individuals at beginning of the universe
     * @param[in] nb_individuals number of individuals
     * @param[in] nb_max_individuals max number of individuals
     * @param[in] environment environment
     * @param[in] buffer buffer
    */
    Universe(std::string name, Individual** individuals, int nb_individuals, int nb_max_individuals, Environment* environment, Buffer* buffer);


    /**
     * @brief perform one environment step 
    */
    void next_step_environment();

    /**
     * @brief perform one step for the given individual
     * 
     * @param[in] individual_index index of the individual in the array of individuals
    */
    void next_step_individual(int individual_nb);

    /**
     * @brief perform on step for all the individuals
    */
    void next_step_individuals();

    /**
     * @brief Proceed to the next step
    */
    void next_step();

    /**
     * @brief Prepare some values for the individuals
     * 
     * Make the environment compute values and set them into the individuals inputs
     * 
     * @param[in] nb_values number of values to prepare
     * 
     * @return inputs for the individuals
    */
    Flow** prepare_values(int nb_vals);

    /**
     * @brief Make the individuals compute and get their outputs
     * 
     * @param[in] vals values to compute
    */
    Flow** individuals_compute(Flow** vals);

    /**
     * @brief compute the errors between labels and predictions
     * 
     * @param[in] inputs input given to the individuals
     * @param[in] outputs output (predictions) of the individuals
     * @param[in] nb_flows number of individuals
    */
    double* compute_errors(Flow** inputs, Flow** outputs, int nb_flows);

    /**
     * @brief Show the universe
    */
    void show();

    //----- getters
    std::string get_name();
    int get_nb_individuals();
    Individual** get_individuals();
    int getWidth();
    int getHeight();

    //----- other
    std::string to_string();
};