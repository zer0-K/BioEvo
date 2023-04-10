#include "Buffer.hpp"

Buffer::Buffer()
{

}

void Buffer::feed_ins_and_outs(Individual* individual, Environment* environment)
{
    // get outputs
    Flow* individual_output = individual->get_output();
    Flow* environment_output = environment->get_output();

    // transforms the outputs into inputs for the other
    Flow* input_for_individual = this->transform_environment_out_to_individual_in(environment_output);
    Flow* input_for_environment = this->transform_individual_out_to_environment_in(individual_output);

    // feed the inputs
    individual->set_input(input_for_individual);
    environment->set_input(input_for_environment);
}