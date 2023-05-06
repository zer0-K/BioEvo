#include "Buffer.hpp"

#include <iostream>

#include "../../Utils/Log/Logger.hpp"
#include "../../Declaration/Constants.hpp"

Buffer::Buffer()
{

}

void Buffer::feed_ins_and_outs(std::vector<sp_individual> individuals, sp_environment environment)
{
    logger_write(3, FLAG_INFO + FLAG_EVOLVE + FLAG_BEGIN + "Feeding ins and outs");

    // get outputs
    sp_flow environment_out = environment->get_output();
    std::vector<sp_flow> individuals_out;
    for(int i=0;i<individuals.size();i++)
    {
        individuals_out[i] = individuals[i]->get_output();
    } 


    // transforms the outputs into inputs for the other
    sp_flow input_for_environment = this->transform_individuals_out_to_environment_in(individuals_out);
    std::vector<sp_flow> inputs_for_individuals = this->transform_environment_out_to_individuals_in(environment_out, individuals.size()); 

    // feed the inputs
    environment->set_input(input_for_environment);
    for(int i=0;i<individuals.size();i++)
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
