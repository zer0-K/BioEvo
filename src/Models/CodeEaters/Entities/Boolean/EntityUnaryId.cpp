#include "EntityUnaryId.hpp"

#include "../../../../Utils/Constants.hpp"

void EntityUnaryId::init()
{
    EntityOperationBoolean::init();

    type = TYPE_UID;
    add_type(TYPE_UID);
}

std::vector<sp_entity> EntityUnaryId::exec(std::vector<sp_entity> entries)
{
    // apply id for each entity, for each type-0 attribute 
    for(int i=0;i<entries.size();i++)
    {
        bool is_applied = false;

        if(entries[i]->has_value_int())
        {
            is_applied = true;

            // basic int id
            entries[i]->set_value_int(entries[i]->get_value_int());
        }

        if(entries[i]->has_value_double())
        {
            is_applied = true;

            // basic double id
            entries[i]->set_value_double(entries[i]->get_value_double());
        }

        if(entries[i]->has_value_str())
        {
            is_applied = true;

            // basic str id
            entries[i]->set_value_str(entries[i]->get_value_str());
        }

        if(entries[i]->has_value_bool())
        {
            is_applied = true;

            // basic bool id
            entries[i]->set_value_bool(entries[i]->get_value_bool());
        }

        if(is_applied)
        {
            increase_op_counter();
        }
    }

    return entries;
}