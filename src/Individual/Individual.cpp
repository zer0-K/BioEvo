#include "Individual.hpp"

#include <iostream>

#include "../Declaration/PreprocessingDefinitions.hpp"
#include "../Declaration/Constants.hpp"
#include "../Utils/Log/Logger.hpp"

Individual::Individual(std::string name)
    :Individual::Individual(name, DEFAULT_NB_EPOCHS_LEARN)
{
    // nothing here
}

Individual::Individual(std::string name, int nb_epoch_learn)
    :Entity::Entity(name)
{
    logger_write(1, FLAG_INIT + FLAG_BEGIN + "Creating individual. name : " + name);

    this->number_of_epochs = nb_epoch_learn;

    // inputs and outputs must be initialized explicitly
    this->input = nullptr;
    this->output = nullptr;

    logger_write(1, FLAG_INIT + FLAG_END + this->name + " created");
    logger_write(7, FLAG_INIT + FLAG_END + this->name + " number of epochs for learning : " + std::to_string(this->number_of_epochs));
}

Individual::Individual(boost::json::object params)
    :Entity::Entity(params)
{
    this->number_of_epochs = DEFAULT_NB_EPOCHS_LEARN;
}

//---------- getters

std::shared_ptr<Flow> Individual::get_output()
{
    return this->output;
}

//---------- setters

void Individual::set_input(std::shared_ptr<Flow> input)
{
    // set new input
    this->input = std::move(input);
}

void Individual::set_output(std::shared_ptr<Flow> output)
{
    // set new input
    this->output = std::move(output);
}

void Individual::set_number_of_epochs(int nb_epoch_learn)
{
    this->number_of_epochs = nb_epoch_learn;
}

//---------- other

boost::json::object Individual::object_to_json()
{
    boost::json::object jindividual;

    jindividual["name"] = name;
    jindividual["nb epochs"] = number_of_epochs;

    return jindividual;
}

std::string Individual::to_string()
{
    std::string res = "";

    res += this->name + " : " + std::to_string(this->number_of_epochs) + " epochs ";
    res += "(input : " + this->input->to_string() + " ; output : " + this->output->to_string() + ")";

    return res;
}

std::string Individual::is_ready()
{
    bool is_ready = true;
    std::string message = "Individual missing content : ";

    if(this->name == "")
    {
        is_ready = false;
        message += "name, ";
    }
    else
    {
        message = this->name + " missing content : ";
    }

    if(this->input == nullptr)
    {
        is_ready = false;
        message += "input, ";
    }

    if(is_ready)
        return "ready";

    return message;
}