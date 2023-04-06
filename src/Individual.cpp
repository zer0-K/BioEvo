#include "Individual.hpp"

Individual::Individual()
{

}

void Individual::set_input(Flow* input)
{
    // set new input
    Flow* old_input = this->input;
    this->input = input;
    delete old_input;
}

Flow* Individual::get_output()
{
    return this->output;
}