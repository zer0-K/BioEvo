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
     * @param[in] individual_output individual's ouput to feed the environment with
     * 
     * @return input for environment
    */
    virtual Flow* transform_individual_out_to_environment_in(Flow* individual_ouput) = 0;

    /**
     * @brief Transform environment's output into individial's input
     * 
     * @param[in] environment_output environment's ouput to feed the individial with
     * 
     * @return input for the individual
    */
    virtual Flow* transform_environment_out_to_individual_in(Flow* environment_ouput) = 0;

    /**
     * @brief Feed individual output to environment input and environment output to individual output
     * 
     * @param[in] individual individual
     * @param[in] environment environment
    */
    void feed_ins_and_outs(Individual* individual, Environment* environment);
};