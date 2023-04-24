#pragma once

#include "Flow.hpp"
#include "Individual.hpp"
#include "Environment.hpp"

/// @brief buffer 'interface' to feed the outputs of ones to the inputs of others
class Buffer
{
public:
    /**
     * @brief Constructor
    */
    Buffer();

    /**
     * @brief Transform individial's output into environment's input
     * 
     * @param[in] individuals_outputs individuals' ouputs to feed the environment with
     * 
     * @return input for the environment
     */
    virtual Flow* transform_individuals_out_to_environment_in(Flow** individuals_ouputs) = 0;

    /**
     * @brief Transform environment's output into individial's input
     * 
     * @param[in] environment_output environment's ouput to feed the individials with
     * @param[in] nb_individuals number of individuals
     * 
     * @return inputs of the individuals
    */
    virtual Flow** transform_environment_out_to_individuals_in(Flow* environment_ouput, int nb_individuals) = 0;

    /**
     * @brief Compute the error between the label and the prediction
     * 
     * @param[in] input input given to individual
     * @param[in] output output (predictions) of the individual
     * 
     * @return array of the errors
    */
    virtual double compute_errors(Flow* input, Flow* output)=0;

    /**
     * @brief Feed individuals output to environment input and environment output to individuals input
     * 
     * Can be overriden
     * By default, consider that the environment's input and output are fit for an array of individual
     * For example, if there are 4 individuals, it considers the environment output is an array of 4 individuals' inputs
     * 
     * @param[in] individuals individuals
     * @param[in] nb_individuals number of individuals
     * @param[in] environment environment
    */
    void feed_ins_and_outs(Individual** individuals, int nb_individuals, Environment* environment);

    //----- other
    std::string to_string();
    std::string to_json();
};