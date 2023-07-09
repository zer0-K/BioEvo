#include "EntityInt.hpp"

#include "../Utils/Constants.hpp"

void EntityInt::init()
{
    type = TYPE_INT;
    add_type(TYPE_INT);
    has_int = true;
}