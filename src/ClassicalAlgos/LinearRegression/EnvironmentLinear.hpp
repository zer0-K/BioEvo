#pragma once

#include "../../Environment.hpp"

/// @brief environment generating linear functions
class EnvironmentLinear : Environment
{
protected:
    int dimension;  ///< dimension 
    double* w;  ///< the coefficients of the linear model
    double b;   ///< affine term

public:
    /**
     * @brief Constructor
     * 
     * @param[in] name name of the environment
     * @param[in] dimension dimension of the linear model
     * @param[in] w linear coefficients of the linear model
     * @param[in] b affine term 
    */
    EnvironmentLinear(std::string name, int dimension, double* w, double b);

    /// @see Environment::evolve
    void evolve() override;
};