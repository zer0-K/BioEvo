#include "EntityNot.hpp"

#include "../../../../../Utils/Constants.hpp"

void EntityNot::init()
{
    EntityOperationBoolean::init();

    type = TYPE_NOT;
    add_type(TYPE_NOT);
}

std::vector<sp_entity> EntityNot::exec(std::vector<sp_entity> entries)
{
    // apply not on the second entity into the first
    if(entries.size() == 2)
    {
        if(entries[0]->has_value_bool()
            && entries[1]->has_value_bool())
        {
            increase_op_counter();

            entries[0]->set_value_bool(
                !entries[1]->get_value_bool()
            );
        }
    }

    return entries;
}