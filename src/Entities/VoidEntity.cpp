#include "VoidEntity.hpp"

#include "../Utils/Constants.hpp"

VoidEntity::VoidEntity(std::string entity_name)
    :Entity::Entity(entity_name, TYPE_VOID)
{
}

VoidEntity::VoidEntity(std::string entity_name, int val)
    :Entity::Entity(entity_name, TYPE_VOID, val)
{
}

VoidEntity::VoidEntity(std::string entity_name, double val)
    :Entity::Entity(entity_name, TYPE_VOID, val)
{
}

VoidEntity::VoidEntity(std::string entity_name, std::string val)
    :Entity::Entity(entity_name, TYPE_VOID, val)
{
}

VoidEntity::VoidEntity(std::string entity_name, bool val)
    :Entity::Entity(entity_name, TYPE_VOID, val)
{
}

std::vector<sp_entity> VoidEntity::exec(std::vector<sp_entity> entries)
{
    return std::vector<sp_entity>(0);
}