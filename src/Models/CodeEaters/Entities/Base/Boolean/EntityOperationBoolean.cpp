#include "EntityOperationBoolean.hpp"

#include "../../../../../Utils/Constants.hpp"

void EntityOperationBoolean::init()
{
    EntityOperation::init();

    type = TYPE_OP_BOOL;
    add_type(TYPE_OP_BOOL);
}

std::vector<sp_entity> EntityOperationBoolean::exec(std::vector<sp_entity> entries)
{
    // does nothing

    return entries;
}
