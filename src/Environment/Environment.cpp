#include "Environment.hpp"

#include "../Declaration/PreprocessingDefinitions.hpp"
#include "../Declaration/Constants.hpp"
#include "../Utils/Log/Logger.hpp"

Environment::Environment(std::string name, size_t size)
    :Entity::Entity(name)
{
    env_values = std::vector<QuantumDataAbstract>(size);
}

Environment::Environment(boost::json::object params)
    :Entity::Entity(params)
{
    // only set size
    boost::json::value* jsize = params.if_contains("size");

    if(jsize != nullptr)
        env_values = std::vector<QuantumDataAbstract>(boost::json::value_to<int>(*jsize));
}

std::string Environment::to_string()
{
    std::string res = "";

    res += name + " : size : " + std::to_string(env_values.size());

    return res;
}

boost::json::object Environment::object_to_json()
{
    boost::json::object jenv;

    jenv["name"] = name;
    jenv["size"] = env_values.size();

    return jenv;
}

std::string Environment::is_ready()
{
    bool is_ready = true;
    std::string message = "Environment missing content : ";

    if(name == "")
    {
        is_ready = false;
        message += "name, ";
    }
    else
    {
        message = "Missing content of " + name + " : ";
    } 

    if(is_ready)
        return "ready";
    
    return message;
}