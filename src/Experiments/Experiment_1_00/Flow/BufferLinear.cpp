#include "BufferLinear.hpp"

#include "InputLinearEnvironment.hpp"
#include "InputLinearIndividual.hpp"
#include "OutputLinearEnvironment.hpp"
#include "OutputLinearIndividual.hpp"
#include <iostream>
#include <math.h>

Flow* BufferLinear::transform_individuals_out_to_environment_in(Flow** individuals_ouputs)
{
   return NULL; 
}

Flow** BufferLinear::transform_environment_out_to_individuals_in(Flow* environment_ouput, int nb_individuals)
{
    Pair<double,double>*** output_values = ((OutputLinearEnvironment*) environment_ouput)->get_values();
    int* nb_vals = ((OutputLinearEnvironment*) environment_ouput)->get_nb_vals();

    Flow** individuals_inputs = new Flow*[nb_individuals];
    for(int i=0; i<nb_individuals; i++)
    {
        individuals_inputs[i] = (Flow*) new InputLinearIndividual(output_values[i], nb_vals[i]);
    }

    return individuals_inputs;
}

double BufferLinear::compute_errors(Flow* input, Flow* output)
{
    InputLinearIndividual* input_linear = (InputLinearIndividual*) input;
    OutputLinearIndividual* output_linear = (OutputLinearIndividual*) output;

    int nb_vals = input_linear->get_nb_vals();
    auto input_vals = input_linear->get_values();
    auto output_vals = output_linear->get_values();
    
    double gap = 0;
    double error = 0;

    if(nb_vals == output_linear->get_nb_vals() && nb_vals>0)
    {        
        for(int i=0;i<nb_vals;i++) 
        {
            gap = output_vals[i]->get_f_x() - input_vals[i]->get_f_x();
            error += gap*gap;
        }
        error /= (double) nb_vals;
    }

    return error;
}