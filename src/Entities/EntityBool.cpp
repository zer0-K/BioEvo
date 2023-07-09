#include "EntityBool.hpp"

#include "../Utils/Constants.hpp"

void EntityBool::init()
{
    type = TYPE_BOOL;
    add_type(TYPE_BOOL);
    has_bool = true;
}