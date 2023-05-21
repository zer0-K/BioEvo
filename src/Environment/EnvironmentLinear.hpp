#pragma once

#include <vector>

#include "EnvironmentClassical.hpp"
#include "../Utils/Math/Pair.hpp"

/// @brief environment generating linear functions
class EnvironmentLinear : public EnvironmentClassical
{
protected:
    int dimension;  ///< dimension 
    std::vector<double> w;     ///< the coefficients of the linear model
    double b;   ///< affine term

    /**
     * @brief generate a random x to compute the linear transformation from
     * 
     * @return random x
    */
    std::vector<double> generate_random_x();
    
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
     * @param[in] size_test size of test data
     * @param[in] size_validation size of validation
     * @param[in] dimension dimension of the linear model
     * @param[in] w linear coefficients of the linear model
     * @param[in] b affine term 
    */
    EnvironmentLinear(std::string name, size_t size_test, size_t size_validation, int dimension, std::vector<double> w, double b);

    /**
     * @brief @see Entity constructor
    */
    EnvironmentLinear(boost::json::object params);

    /// @see Environment::evolve
    void evolve() override;

    /// @see Environment::init_values
    void init_values() override;

    //----- other
    std::string to_string();
    boost::json::object object_to_json() override;

    static boost::json::object type_to_json()
    {
        boost::json::object jenv = Environment::type_to_json();

        jenv["dimension"]   =   TYPE_INT;
        jenv["weights"]     =   TYPE_LIST + "-" + TYPE_DOUBLE;
        jenv["bias"]        =   TYPE_DOUBLE;

        return jenv;
    }
};

typedef std::shared_ptr<EnvironmentLinear> sp_environment_linear;