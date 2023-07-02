#include "LinearEntity.hpp"

#include <cstdlib>

#include "../../../Utils/Constants.hpp"
#include "../../../Utils/Maths/RandomGen.hpp"

LinearEntity::LinearEntity(std::string entity_name)
    :Entity::Entity(entity_name, TYPE_LINEAR)
{
}

std::vector<sp_entity> LinearEntity::exec(std::vector<sp_entity> entries)
{
    
    int test = rand()%100;
    return std::vector<sp_entity>(0);
}