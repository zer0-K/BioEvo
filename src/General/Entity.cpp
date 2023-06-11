#include "Entity.hpp"

Entity::Entity(std::string entity_name, std::string type)
{
    name = entity_name;
    this->type = type;

    working_place_index = 0;
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

int Entity::get_working_place_index()
{
    return working_place_index;
}