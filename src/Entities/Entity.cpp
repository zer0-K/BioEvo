#include "Entity.hpp"

Entity::Entity(std::string entity_name)
{
    name = entity_name;

    has_int = false;
    has_double = false;
    has_str = false;
    has_bool = false;

    working_place_index = 0;
}

Entity::Entity(std::string entity_name, int val)
    :Entity::Entity(entity_name)
{
    has_int = true;
    value_int = val;
}

Entity::Entity(std::string entity_name, double val)
    :Entity::Entity(entity_name)
{
    has_double = true;
    value_double = val;
}

Entity::Entity(std::string entity_name, std::string val)
    :Entity::Entity(entity_name)
{
    has_str= true;
    value_str = val;
}

Entity::Entity(std::string entity_name, bool val)
    :Entity::Entity(entity_name)
{
    has_bool = true;
    value_bool = val;
}

std::vector<sp_entity> Entity::exec(sp_entity entry)
{
    std::vector<sp_entity> entries {
        entry
    };

    return exec(entries);
}

std::string Entity::get_name()
{
    return name;
}

std::string Entity::get_type()
{
    return type;
}

bool Entity::has_value_int()
{
    return has_int;
}

int Entity::get_value_int()
{
    return value_int;
}

bool Entity::has_value_double()
{
    return has_double;
}

double Entity::get_value_double()
{
    return value_double;
}

bool Entity::has_value_str()
{
    return has_str;
}

std::string Entity::get_value_str()
{
    return value_str;
}

bool Entity::has_value_bool()
{
    return has_bool;
}

bool Entity::get_value_bool()
{
    return value_bool;
}

int Entity::get_working_place_index()
{
    return working_place_index;
}

//---------- setters

void Entity::set_value_int(int val)
{
    value_int = val;
}

void Entity::set_value_double(double val)
{
    value_double = val;
}

void Entity::set_value_str(std::string val)
{
    value_str = val;
}

void Entity::set_value_bool(bool val)
{
    value_bool = val;
}