#include "EntityList.hpp"

#include "../Utils/Constants.hpp"

void EntityList::init()
{
    type = TYPE_LIST;
}

std::vector<sp_entity> EntityList::exec(std::vector<sp_entity> entries)
{
    return std::vector<sp_entity>(0);
}