#include "InputLinearIndividual.hpp"

InputLinearIndividual::InputLinearIndividual(Pair<double,double>* input_vals[], int nb_vals)
{
    this->input_values = input_vals;
    this->nb_vals = nb_vals;
}


//---------- getters

Pair<double,double>** InputLinearIndividual::get_values()
{
    return this->input_values;
}

int InputLinearIndividual::get_nb_vals()
{
    return this->nb_vals;
}