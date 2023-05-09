#include "Environment.hpp"

#include "../Declaration/PreprocessingDefinitions.hpp"
#include "../Declaration/Constants.hpp"
#include "../Utils/Log/Logger.hpp"

Environment::Environment(std::string name)
    :Environment::Environment(name, DEFAULT_NB_EPOCHS_EVO)
{
    // do nothing here
}

Environment::Environment(std::string name, int nb_epochs_evo)
    :Entity::Entity(name)
{
    logger_write(2, FLAG_INIT + "Creating environment. name : " + name);

    this->number_of_epochs = nb_epochs_evo;

    logger_write(1, FLAG_INIT + this->name + " created");
    logger_write(7, FLAG_INIT + FLAG_END + this->name + " number of epochs for evolution : " + std::to_string(this->number_of_epochs));
}

Environment::Environment(boost::json::object params)
    :Entity::Entity(params)
{

}

//---------- getters

sp_flow Environment::get_output()
{
    return this->output;
}

//---------- setters

void Environment::set_input(sp_flow input)
{
    logger_write(2, FLAG_INFO + FLAG_BEGIN + "Setting input of " + this->name);
    
    this->input = input;
    
    logger_write(2, FLAG_INFO + FLAG_END + "Input of " + this->name + ". Input : " + input->to_string());
}

void Environment::set_output(sp_flow output)
{
    logger_write(2, FLAG_INFO + FLAG_BEGIN + "Setting output of " + this->name);

    this->output = output;

    logger_write(2, FLAG_INFO + FLAG_END + "Input of " + this->name + " set");
}

std::string Environment::to_string()
{
    std::string res = "";

    res += this->name + " : " + std::to_string(this->number_of_epochs) + " epochs ";
    res += "(input : " + this->input->to_string() + " ; output : " + this->output->to_string() + ")";

    return res;
}

boost::json::object Environment::object_to_json()
{
    boost::json::object jenv;

    jenv["name"] = this->name;

    return jenv;
}

std::string Environment::is_ready()
{
    bool is_ready = true;
    std::string message = "Environment missing content : ";

    if(this->name == "")
    {
        is_ready = false;
        message += "name, ";
    }
    else
    {
        message = "Missing content of " + this->name + " : ";
    } 

    if(is_ready)
        return "ready";
    
    return message;
}