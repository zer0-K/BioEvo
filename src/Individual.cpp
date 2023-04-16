#include "Individual.hpp"

#include <iostream>

#include "PreprocessingDefinitions.hpp"
#include "Constants.hpp"
#include "Utils/Log/Logger.hpp"

Individual::Individual(std::string name)
    :Individual::Individual(name, DEFAULT_NB_EPOCHS_LEARN)
{
    // nothing here
}

Individual::Individual(std::string name, int nb_epoch_learn)
{
    logger_write(1, FLAG_INIT + FLAG_BEGIN + "Creating individual. name : " + name);

    this->name = name;
    this->number_of_epochs = nb_epoch_learn;

    logger_write(1, FLAG_INIT + FLAG_END + this->name + " created");
    logger_write(7, FLAG_INIT + FLAG_END + this->name + " number of epochs for learning : " + std::to_string(this->number_of_epochs));
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
    logger_write(2, FLAG_INFO + FLAG_BEGIN + "Setting input of " + this->name);

    // set new input
    this->input = input;
    
    logger_write(2, FLAG_INFO + FLAG_END + "Input of " + this->name + " set");
}

void Individual::set_output(Flow* output)
{
    logger_write(2, FLAG_INFO + FLAG_BEGIN + "Setting output of " + this->name);

    // set new input
    Flow* old_output = this->output;
    this->output = output;
    delete old_output;

    logger_write(2, FLAG_INFO + FLAG_END + "Input of " + this->name + " set");
}

void Individual::set_number_of_epochs(int nb_epoch_learn)
{
    this->number_of_epochs = nb_epoch_learn;
}

//---------- other

std::string Individual::to_string()
{
    std::string res = "";

    res += this->name + " : " + std::to_string(this->number_of_epochs) + " epochs ";
    res += "(input : " + this->input->to_string() + " ; output : " + this->output->to_string() + ")";

    return res;
}