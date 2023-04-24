#include "InputLinearIndividual.hpp"

#include "../../../Utils/Convert/tostring.hpp"
#include "../../../Constants.hpp"

InputLinearIndividual::InputLinearIndividual(Pair<double,double>** input_vals, int nb_vals)
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


//---------- other

std::string InputLinearIndividual::to_string(int dimension)
{
    std::string res = Flow::to_string();

    for(int i=0;i<std::min(nb_vals, MAX_ARRAY_PRINT);i++)
    {
        double f_x = this->input_values[i]->get_f_x();
        res += "f(" + convert_str(this->input_values[i]->get_x(), dimension) + ") = " + std::to_string(f_x);
    }

    return res;
}