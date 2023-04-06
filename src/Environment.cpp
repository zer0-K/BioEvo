#include "Environment.hpp"

Environment::Environment()
{

}

void Environment::set_input(Flow* input)
{
    // set new input
    Flow* old_input = this->input;
    this->input = input;
    delete old_input;
}

Flow* Environment::get_output()
{
    return this->output;
}