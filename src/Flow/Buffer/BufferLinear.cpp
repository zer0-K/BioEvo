#include "BufferLinear.hpp"

#include "../InputLinearEnvironment.hpp"
#include "../InputLinearIndividual.hpp"
#include "../OutputLinearEnvironment.hpp"
#include "../OutputLinearIndividual.hpp"
#include <iostream>
#include <math.h>

sp_flow BufferLinear::transform_individuals_out_to_environment_in(std::vector<sp_flow> individuals_ouputs)
{
   return NULL; 
}

std::vector<sp_flow> BufferLinear::transform_environment_out_to_individuals_in(sp_flow environment_ouput, int nb_individuals)
{
    sp_output_linear_environment outlinenv = std::dynamic_pointer_cast<OutputLinearEnvironment>(
        environment_ouput
    );
    Pair<double,double>*** output_values = outlinenv->get_values();
    int* nb_vals = outlinenv->get_nb_vals();

    std::vector<sp_flow> individuals_inputs;
    for(int i=0; i<nb_individuals; i++)
    {
        individuals_inputs[i] = std::make_shared<InputLinearIndividual>(output_values[i], nb_vals[i]);
    }

    return individuals_inputs;
}

double BufferLinear::compute_errors(sp_flow input, sp_flow output)
{
    sp_input_linear_individual input_linear = std::dynamic_pointer_cast<InputLinearIndividual>(
        input
    );
    sp_output_linear_individual output_linear = std::dynamic_pointer_cast<OutputLinearIndividual>(
        output
    );

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