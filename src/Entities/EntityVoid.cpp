#include "EntityVoid.hpp"

#include "../Utils/Constants.hpp"

void EntityVoid::init()
{
    type = TYPE_VOID;
    add_type(TYPE_VOID);
}

std::vector<sp_entity> EntityVoid::exec(std::vector<sp_entity> entries)
{
    return std::vector<sp_entity>(0);
}