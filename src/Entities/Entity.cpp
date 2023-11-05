#include "Entity.hpp"

#include "../Utils/Constants.hpp"

Entity::Entity(std::string entity_name)
{
    name = entity_name;
    type = TYPE_ENTITY;

    types = std::vector<std::string>(0);
    add_type(type);

    has_int = false;
    has_double = false;
    has_str = false;
    has_bool = false;

    connected_in = std::vector<int>(0);
    connected_outs = std::vector<int>(0);

    nb_of_uses = 0;
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

void Entity::add_type(std::string given_type)
{
    // check whether the given type is already in the types
    bool isin = false;
    std::string type_curr;
    for(int i=0;i<types.size();i++)
    {
        if(types[i] == given_type)
        {
            isin = true;
            break;
        }
    }

    if(!isin)
    {
        types.push_back(given_type);
    }
}

//---------- getters

std::string Entity::get_name()
{
    return name;
}

std::string Entity::get_type()
{
    return type;
}

std::string Entity::get_type(int i)
{
    if(i<0 || i>types.size()-1)
    {
        return TYPE_ENTITY;
    }
    else
    {
        return types[i];
    }
}

bool Entity::is_type(std::string type_to_check)
{
    for(int i=0;i<types.size();i++)
    {
        if(types[i] == type_to_check)
        {
            return true;
        }
    }

    return false;
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

std::vector<int> Entity::get_connected_ins()
{
    return connected_in;
}

std::vector<int> Entity::get_connected_outs()
{
    return connected_outs;
}

std::vector<sp_entity> Entity::get_input()
{
    return input;
}

std::vector<sp_entity> Entity::get_output()
{
    return output;
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

void Entity::set_op_counter(sp_entity counter)
{
    if(counter->is_type(TYPE_OP_COUNTER))
    {
        op_counter = counter;
    }
}

void Entity::set_connected_in(int new_in)
{
    if(connected_in.size() == 0)
    {
        connected_in.push_back(new_in);
    }
    else
    {
        connected_in[0] = new_in;
    }
}

void Entity::reset_connected_outs()
{
    connected_outs = std::vector<int>(0);
}

void Entity::add_connected_out(int new_out)
{
    bool isin = false;
    for(int i=0;i<connected_outs.size();i++)
    {
        if(new_out == connected_outs[i])
        {
            isin = true;
            break;
        }
    }

    if(!isin)
    {
        connected_outs.push_back(new_out);
    }
}

void Entity::remove_connected_out(int new_out)
{
    int pos= -1;
    for(int i=0;i<connected_outs.size();i++)
    {
        if(new_out == connected_outs[i])
        {
            pos = i;
            break;
        }
    }

    if(pos != -1)
    {
        for(int i=pos;i<connected_outs.size()-1;i++)
        {
            connected_outs[i] = connected_outs[i+1];
        }
        connected_outs.pop_back();
    }
}

void Entity::set_input(std::vector<sp_entity> new_input)
{
    input = new_input;
}

void Entity::set_output(std::vector<sp_entity> new_output)
{
    output = new_output;
}