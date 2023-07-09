#include "EntityNotIn.hpp"

#include "../../../../Utils/Constants.hpp"

void EntityNotIn::init()
{
    EntityOperationBoolean::init();

    type = TYPE_NOTIN;
    add_type(TYPE_NOTIN);
}

std::vector<sp_entity> EntityNotIn::exec(std::vector<sp_entity> entries)
{
    // apply not on the second entity into the first
    if(entries.size() == 1)
    {
        if(entries[0]->has_value_bool())
        {
            increase_op_counter();

            entries[0]->set_value_bool(
                !entries[0]->get_value_bool()
            );
        }
    }

    return entries;
}