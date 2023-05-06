#pragma once

#include <vector>

#include "Flow.hpp"
#include "../Utils/Math/Pair.hpp"

/// @brief output of linear environment 
class OutputLinearEnvironment : public Flow
{
private:
    /**
     * @brief output of the environment
     * 
     * Array for the inputs of the individuals
     * An individual input in a linear model is an array of tagged points for learning
    */
    Pair<double,double>*** output_values;
    std::vector<int> nb_vals;   ///< number of values for each individuals

public:
    /**
     * @brief Constructor
     * 
     * @param[in] vals output of the environment 
     * @param[in] nb_vals number of values
    */
    OutputLinearEnvironment(Pair<double,double>*** vals, std::vector<int> nb_vals);

    /**
     * getters
    */

    Pair<double,double>*** get_values();
    std::vector<int> get_nb_vals();
};

typedef std::shared_ptr<OutputLinearEnvironment> sp_output_linear_environment;