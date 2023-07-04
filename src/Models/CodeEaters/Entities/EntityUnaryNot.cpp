#include "EntityUnaryNot.hpp"

#include "../../../Utils/Constants.hpp"

void EntityUnaryNot::init()
{
    type = TYPE_UNOT;
}

std::vector<sp_entity> EntityUnaryNot::exec(std::vector<sp_entity> entries)
{
    // apply id for each entity, for each type-0 attribute 
    for(int i=0;i<entries.size();i++)
    {
        if(entries[i]->has_value_bool())
        {
            // basic bool not
            bool old_value = entries[i]->get_value_bool(); 
            entries[i]->set_value_bool( !old_value );
        }

    }

    return entries;
}