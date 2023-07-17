#include "EntityBoolIdIn.hpp"

#include "../../../../../Utils/Constants.hpp"

void EntityBoolIdIn::init()
{
    EntityOperationBoolean::init();

    type = TYPE_BOOLIDIN;
    add_type(TYPE_BOOLIDIN);
}

std::vector<sp_entity> EntityBoolIdIn::exec(std::vector<sp_entity> entries)
{
    // apply id in place (i.e. does nothing except taking time)
    if(entries.size() == 1)
    {
        if(entries[0]->has_value_bool())
        {
            increase_op_counter();

            entries[0]->set_value_bool(
                entries[0]->get_value_bool()
            );
        }
    }

    return entries;
}