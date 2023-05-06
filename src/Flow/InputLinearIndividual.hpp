#pragma once

#include "Flow.hpp"
#include "../Utils/Math/Pair.hpp"

/// @brief input of linear models
class InputLinearIndividual : public Flow
{
private:
    /**
     * @brief input of the environment
     * 
     * Array for the inputs of the individuals
     * An individual input in a linear model is an array of tagged points for learning
    */
    Pair<double,double>** input_values;
    int nb_vals;   ///< number of values

public:
    /**
     * @brief Constructor
     * 
     * @param[in] vals input of the individual 
     * @param[in] nb_vals number of values
    */
    InputLinearIndividual(Pair<double,double>** vals, int nb_vals);

    /**
     * getters
    */

    Pair<double,double>** get_values();
    int get_nb_vals();


    //---- other
    std::string to_string(int dimension);
};

typedef std::shared_ptr<InputLinearIndividual> sp_input_linear_individual;