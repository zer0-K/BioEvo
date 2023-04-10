#pragma once

#include "../../Flow.hpp"

/// @brief flow for linear models
class FlowLinear : Flow
{
private:
    int dimension;      ///< dimension of the linear model
    double* flow_vector;///< vector of values 

public:
    /**
     * @brief Constructor
     * 
     * @param[in] dimension dimension of the linear model
     * @param[in] flow_vector vector of values
    */
    FlowLinear(int dimension, double* flow_vector);
};