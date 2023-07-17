#include "EntityMetaOp.hpp"

#include "../../../../../Utils/Constants.hpp"

void EntityMetaOp::init()
{
    type = TYPE_META;
    add_type(TYPE_META);
}

std::vector<sp_entity> EntityMetaOp::exec(std::vector<sp_entity> entries)
{
    // does nothing

    return entries;
}