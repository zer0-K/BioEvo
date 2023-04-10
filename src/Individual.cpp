#include "Individual.hpp"

Individual::Individual(std::string name)
{
    this->name = name;
}


//---------- getters

std::string Individual::get_name()
{
    return this->name;
}

Flow* Individual::get_output()
{
    return this->output;
}

//---------- setters

void Individual::set_input(Flow* input)
{
    // set new input
    Flow* old_input = this->input;
    this->input = input;
    delete old_input;
}
