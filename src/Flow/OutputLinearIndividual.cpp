#include "OutputLinearIndividual.hpp"

OutputLinearIndividual::OutputLinearIndividual(Pair<double,double>* input_vals[], int nb_vals)
{
    this->input_values = input_vals;
    this->nb_vals = nb_vals;
}


//---------- getters

Pair<double,double>** OutputLinearIndividual::get_values()
{
    return this->input_values;
}

int OutputLinearIndividual::get_nb_vals()
{
    return this->nb_vals;
}