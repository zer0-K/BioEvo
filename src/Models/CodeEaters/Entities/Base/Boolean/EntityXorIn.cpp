#include "EntityXorIn.hpp"

#include "../../../../../Utils/Constants.hpp"

void EntityXorIn::init()
{
    EntityOperationBoolean::init();

    type = TYPE_XORIN;
    add_type(TYPE_XORIN);
}

std::vector<sp_entity> EntityXorIn::exec(std::vector<sp_entity> entries)
{
    if(entries.size() == 2)
    {
        if(entries[0]->has_value_bool()
            && entries[1]->has_value_bool())
        {
            increase_op_counter();

            entries[0]->set_value_bool(
                entries[0]->get_value_bool() ^ entries[1]->get_value_bool()
            );
        }
    }

    return entries;
}