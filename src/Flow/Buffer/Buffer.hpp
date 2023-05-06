#pragma once

#include <vector>

#include "../Flow.hpp"
#include "../../Individual/Individual.hpp"
#include "../../Environment/Environment.hpp"

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
    virtual sp_flow transform_individuals_out_to_environment_in(std::vector<sp_flow> individuals_ouputs) = 0;

    /**
     * @brief Transform environment's output into individial's input
     * 
     * @param[in] environment_output environment's ouput to feed the individials with
     * @param[in] nb_individuals number of individuals
     * 
     * @return inputs of the individuals
    */
    virtual std::vector<sp_flow> transform_environment_out_to_individuals_in(sp_flow environment_ouput, int nb_individuals) = 0;

    /**
     * @brief Compute the error between the label and the prediction
     * 
     * @param[in] input input given to individual
     * @param[in] output output (predictions) of the individual
     * 
     * @return array of the errors
    */
    virtual double compute_errors(sp_flow input, sp_flow output)=0;

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
};

typedef std::shared_ptr<Buffer> sp_buffer;