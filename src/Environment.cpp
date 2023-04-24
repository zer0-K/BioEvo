#include "Environment.hpp"
#include "PreprocessingDefinitions.hpp"
#include "Constants.hpp"
#include "Utils/Log/Logger.hpp"

Environment::Environment(std::string name)
    :Environment::Environment(name, DEFAULT_NB_EPOCHS_EVO)
{
    // do nothing here
}

Environment::Environment(std::string name, int nb_epochs_evo)
{
    logger_write(2, FLAG_INIT + "Creating environment. name : " + name);

    this->name = name;
    this->number_of_epochs = nb_epochs_evo;

    logger_write(1, FLAG_INIT + this->name + " created");
    logger_write(7, FLAG_INIT + FLAG_END + this->name + " number of epochs for evolution : " + std::to_string(this->number_of_epochs));
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
    logger_write(2, FLAG_INFO + FLAG_BEGIN + "Setting input of " + this->name);
    
    // set new input
    Flow* old_input = this->input;
    this->input = input;
    delete old_input;

    logger_write(2, FLAG_INFO + FLAG_END + "Input of " + this->name + ". Input : " + input->to_string());
}

void Environment::set_output(Flow* output)
{
    logger_write(2, FLAG_INFO + FLAG_BEGIN + "Setting output of " + this->name);

    // set new input
    Flow* old_output = this->output;
    this->output = output;
    delete old_output;

    logger_write(2, FLAG_INFO + FLAG_END + "Input of " + this->name + " set");
}

std::string Environment::to_string()
{
    std::string res = "";

    res += this->name + " : " + std::to_string(this->number_of_epochs) + " epochs ";
    res += "(input : " + this->input->to_string() + " ; output : " + this->output->to_string() + ")";

    return res;
}

std::string Environment::to_json()
{
    std::string res = "{";

    res += "'name':" + this->name + ",'number of epochs':" + std::to_string(this->number_of_epochs);
    res += ",'input':" + this->input->to_json() + ",'output':" + this->output->to_json();
    res += "}";

    return res;
}