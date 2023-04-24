#include "Buffer.hpp"

#include <iostream>

#include "Utils/Log/Logger.hpp"
#include "Constants.hpp"

Buffer::Buffer()
{

}

void Buffer::feed_ins_and_outs(Individual** individuals, int nb_individuals, Environment* environment)
{
    logger_write(3, FLAG_INFO + FLAG_EVOLVE + FLAG_BEGIN + "Feeding ins and outs");

    // get outputs
    Flow* environment_out = environment->get_output();
    Flow** individuals_out = new Flow*[nb_individuals];
    for(int i=0;i<nb_individuals;i++)
    {
        individuals_out[i] = individuals[i]->get_output();
    } 


    // transforms the outputs into inputs for the other
    Flow* input_for_environment = this->transform_individuals_out_to_environment_in(individuals_out);
    Flow** inputs_for_individuals = this->transform_environment_out_to_individuals_in(environment_out, nb_individuals); 

    // feed the inputs
    environment->set_input(input_for_environment);
    for(int i=0;i<nb_individuals;i++)
    {
        individuals[i]->set_input(inputs_for_individuals[i]);
    }

    logger_write(3, FLAG_INFO + FLAG_EVOLVE + FLAG_BEGIN + "Ins and outs fed");
}

//---------- other

std::string Buffer::to_string()
{
    return "buffer not null";
}

std::string Buffer::to_json()
{
    return "{}";
}