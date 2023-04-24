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
    // set new input
    this->input = input;
}

void Individual::set_output(Flow* output)
{
    // set new input
    this->output = output;
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

std::string Individual::to_json()
{
    std::string res = "{";

    res += "'name':" + this->name + ",'number of epochs'" + std::to_string(this->number_of_epochs);
    res += "'input':" + this->input->to_json() + ",'output':" + this->output->to_json();
    res += "}";

    return res;
}