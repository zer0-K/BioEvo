#include "Environment.hpp"

Environment::Environment(std::string name)
{
    this->name = name;
}

//---------- getters

std::string Environment::get_name()
{
    return this->name;
}

Flow* Environment::get_output()
{
    return this->output;
}

//---------- setters

void Environment::set_input(Flow* input)
{
    // set new input
    Flow* old_input = this->input;
    this->input = input;
    delete old_input;
}