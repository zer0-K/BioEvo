#include "EntityNor.hpp"

#include "../../../../../Utils/Constants.hpp"

void EntityNor::init()
{
    EntityOperationBoolean::init();

    type = TYPE_NOR;
    add_type(TYPE_NOR);
}

std::vector<sp_entity> EntityNor::exec(std::vector<sp_entity> entries)
{
    if(entries.size() == 3)
    {
        if(entries[0]->has_value_bool()
            && entries[1]->has_value_bool()
            && entries[2]->has_value_bool())
        {
            increase_op_counter();

            entries[0]->set_value_bool(
                !(entries[1]->get_value_bool() | entries[2]->get_value_bool())
            );
        }
    }

    return entries;
}