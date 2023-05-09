#include "Entity.hpp"

Entity::Entity(std::string name)
{
    this->name = name;
}

Entity::Entity(boost::json::object params)
{
    boost::json::value* jname = params.if_contains("name");

    if(jname != nullptr)
    {
        name = boost::json::value_to<std::string>(*jname);
    }
}

std::string Entity::get_name()
{
    return name;
}