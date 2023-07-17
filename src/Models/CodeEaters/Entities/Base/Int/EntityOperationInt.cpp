#include "EntityOperationInt.hpp"

#include "../../../../../Utils/Constants.hpp"

void EntityOperationInt::init()
{
    EntityOperation::init();

    type = TYPE_OP_INT;
    add_type(TYPE_OP_INT);
}

std::vector<sp_entity> EntityOperationInt::exec(std::vector<sp_entity> entries)
{
    // does nothing

    return entries;
}