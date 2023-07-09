#include "EntityMeta.hpp"

#include "../../../../Utils/Constants.hpp"

void EntityMeta::init()
{
    type = TYPE_META;
    add_type(TYPE_META);
}

std::vector<sp_entity> EntityMeta::exec(std::vector<sp_entity> entries)
{
    // does nothing

    return entries;
}