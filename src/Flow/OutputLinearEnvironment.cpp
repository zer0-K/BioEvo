#include "OutputLinearEnvironment.hpp"

OutputLinearEnvironment::OutputLinearEnvironment(Pair<double,double>*** vals, std::vector<int> nb_vals)
{
    this->output_values = vals;
    this->nb_vals = nb_vals;
}

//---------- getters

Pair<double,double>*** OutputLinearEnvironment::get_values()
{
    return this->output_values;
}

std::vector<int> OutputLinearEnvironment::get_nb_vals()
{
    return this->nb_vals;
}