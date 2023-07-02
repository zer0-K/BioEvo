#include "EntityList.hpp"

#include "../Utils/Constants.hpp"

EntityList::EntityList(std::string entity_name)
    :Entity::Entity(entity_name, TYPE_VOID)
{
}

EntityList::EntityList(std::string entity_name, int val)
    :Entity::Entity(entity_name, TYPE_VOID, val)
{
}

EntityList::EntityList(std::string entity_name, double val)
    :Entity::Entity(entity_name, TYPE_VOID, val)
{
}

EntityList::EntityList(std::string entity_name, std::string val)
    :Entity::Entity(entity_name, TYPE_VOID, val)
{
}

EntityList::EntityList(std::string entity_name, bool val)
    :Entity::Entity(entity_name, TYPE_VOID, val)
{
}

std::vector<sp_entity> EntityList::exec(std::vector<sp_entity> entries)
{
    return std::vector<sp_entity>(0);
}