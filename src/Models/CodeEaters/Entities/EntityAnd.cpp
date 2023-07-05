#include "EntityAnd.hpp"

#include "../../../Utils/Constants.hpp"

void EntityAnd::init()
{
    type = TYPE_AND;
}

std::vector<sp_entity> EntityAnd::exec(std::vector<sp_entity> entries)
{
    if(entries.size() == 3)
    {
        if(entries[0]->has_value_bool()
            && entries[1]->has_value_bool()
            && entries[2]->has_value_bool())
        {
            entries[0]->set_value_bool(
                entries[1]->get_value_bool() & entries[2]->get_value_bool()
            );
        }
    }

    return entries;
}