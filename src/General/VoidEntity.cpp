#include "VoidEntity.hpp"

#include "../Utils/Constants.hpp"

VoidEntity::VoidEntity(std::string entity_name)
    :Entity::Entity(entity_name, TYPE_VOID)
{
}

std::vector<sp_entity> VoidEntity::exec(std::vector<sp_entity> entries)
{
    return std::vector<sp_entity>(0);
}