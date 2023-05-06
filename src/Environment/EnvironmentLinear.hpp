#pragma once

#include <vector>

#include "Environment.hpp"
#include "../Utils/Math/Pair.hpp"

/// @brief environment generating linear functions
class EnvironmentLinear : public Environment
{
protected:
    int dimension;  ///< dimension 
    std::vector<double> w;     ///< the coefficients of the linear model
    double b;   ///< affine term

    /**
     * @brief Generate a random output
     * 
     * Generate the output for each individual
     * The individuals can have different learning number of epochs
     * 
     * @param[in] nb_epochs_learn numbers of epochs for learning for each individual
    */
    void generate_random_outputs(std::vector<int> nb_epochs_learn);

    /**
     * @brief Generate a random output for a given individual
     * 
     * @param[in] individual_index index of the individual
     * @param[in] nb_vals number of values to generate 
    */
    Pair<double,double>** generate_random_output(int individual_index, int nb_vals);
    
    /**
     * @brief Compute the linear transormation
     * 
     * compute the linear transformation w1*x1 + ... + wn*xn + b
     * 
     * @param[in] x feature to transform
    */
    double compute_linear(std::vector<double> x);

public:
    /**
     * @brief Constructor
     * 
     * @param[in] name name of the environment
     * @param[in] dimension dimension of the linear model
     * @param[in] w linear coefficients of the linear model
     * @param[in] b affine term 
    */
    EnvironmentLinear(std::string name, int dimension, std::vector<double> w, double b);

    /// @see Environment::evolve
    void evolve(std::vector<int> nb_epochs) override;

    /// @see Environment::evolve
    void init(std::vector<int> nb_epochs) override;

    /// @see Environment::compute
    void compute(int nb_individuals, int nb_vals) override;

    //----- other
    std::string to_string();
    boost::json::object to_json();
};