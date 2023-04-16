#pragma once

#include "../../../Flow.hpp"
#include "../../../Utils/Math/Pair.hpp"

/// @brief output of linear environment 
class OutputLinearEnvironment : Flow
{
private:
    /**
     * @brief output of the environment
     * 
     * Array for the inputs of the individuals
     * An individual input in a linear model is an array of tagged points for learning
    */
    Pair<double,double>*** output_values;
    int* nb_vals;   ///< number of values for each individuals

public:
    /**
     * @brief Constructor
     * 
     * @param[in] vals output of the environment 
    */
    OutputLinearEnvironment(Pair<double,double>*** vals, int nb_vals[]);

    /**
     * getters
    */

    Pair<double,double>*** get_values();
    int* get_nb_vals();
};
