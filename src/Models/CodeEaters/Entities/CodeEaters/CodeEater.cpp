#include "CodeEater.hpp"

#include "../../../../Utils/Constants.hpp"

void CodeEater::init()
{
    type = TYPE_CE;
    add_type(TYPE_CE);
}

std::vector<sp_entity> CodeEater::exec(std::vector<sp_entity> entries)
{
    return entries;
}
