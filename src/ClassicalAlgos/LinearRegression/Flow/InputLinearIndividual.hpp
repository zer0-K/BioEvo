#pragma once

#include "../../../Flow.hpp"
#include "../../../Utils/Math/Pair.hpp"

/// @brief input of linear models
class InputLinearIndividual : Flow
{
private:   
    Pair<double,double>** input_values;    ///< values for learning
    int nb_vals;    ///< number of values

public:
    /**
     * @brief Constructor
     * 
     * @param[in] input_vals values for learning 
     * @param[in] nb_vals number of values
    */
    InputLinearIndividual(Pair<double,double>* input_vals[], int nb_vals);

    /**
     * getters
    */

    Pair<double,double>** get_values();
    int get_nb_vals();
};