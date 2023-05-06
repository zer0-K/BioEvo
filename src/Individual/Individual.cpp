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

std::string Individual::to_string()
{
    std::string res = "";

    res += this->name + " : " + std::to_string(this->number_of_epochs) + " epochs ";
    res += "(input : " + this->input->to_string() + " ; output : " + this->output->to_string() + ")";

    return res;
}

boost::json::object Individual::to_json()
{
    boost::json::object jindividual;

    jindividual["name"] = this->name;
    jindividual["nb_epoch"] = this->number_of_epochs;

    /*
    std::string res = "{";

    res += "'name':" + this->name + ",'number of epochs'" + std::to_string(this->number_of_epochs);
    res += "'input':" + this->input->to_json() + ",'output':" + this->output->to_json();
    res += "}";

    return res;*/

    return jindividual;
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

    if(is_ready)
        return "ready";

    return message;
}