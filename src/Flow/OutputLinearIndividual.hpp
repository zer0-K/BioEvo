#pragma once

#include "Flow.hpp"
#include "../Utils/Math/Pair.hpp"

/// @brief output of linear models 
class OutputLinearIndividual : public Flow
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
    OutputLinearIndividual(Pair<double,double>* input_vals[], int nb_vals);

    /**
     * getters
    */

    Pair<double,double>** get_values();
    int get_nb_vals();
};

typedef std::shared_ptr<OutputLinearIndividual> sp_output_linear_individual;