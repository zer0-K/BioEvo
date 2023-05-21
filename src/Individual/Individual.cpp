#include "Individual.hpp"

#include <iostream>

#include "../Declaration/PreprocessingDefinitions.hpp"
#include "../Declaration/Constants.hpp"
#include "../Utils/Log/Logger.hpp"

Individual::Individual(std::string name)
    :Entity::Entity(name)
{
}

Individual::Individual(boost::json::object params)
    :Entity::Entity(params)
{
}

//---------- other

boost::json::object Individual::object_to_json()
{
    boost::json::object jindividual;

    jindividual["name"] = name;

    return jindividual;
}

std::string Individual::to_string()
{
    std::string res = "";

    res += name;

    return res;
}

std::string Individual::is_ready()
{
    bool is_ready = true;
    std::string message = "Individual missing content : ";

    if(name == "")
    {
        is_ready = false;
        message += "name, ";
    }
    else
    {
        message = name + " missing content : ";
    }

    if(is_ready)
        return "ready";

    return message;
}