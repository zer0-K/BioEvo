#include "EntityOperation.hpp"

#include "../../../Utils/Constants.hpp"
#include "Meta/EntityOpCounter.hpp"

void EntityOperation::init()
{
    //Entity::init();

    type = TYPE_OP;
    add_type(TYPE_OP);
}

std::vector<sp_entity> EntityOperation::exec(std::vector<sp_entity> entries)
{
    // does nothing

    return entries;
}

/**
 * By default, increase the op counter by 1
*/
void EntityOperation::increase_op_counter()
{
    if(op_counter != nullptr)
    {
        (std::dynamic_pointer_cast<EntityOpCounter>(op_counter))->add_count(type);
    }
}