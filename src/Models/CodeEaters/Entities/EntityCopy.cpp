#include "EntityCopy.hpp"

#include "../../../Utils/Constants.hpp"

void EntityCopy::init()
{
    type = TYPE_COPY;
}

std::vector<sp_entity> EntityCopy::exec(std::vector<sp_entity> entries)
{
    // copy second entity into the first one
    if(entries.size() == 2)
    {
        if(entries[0]->has_value_int() && entries[1]->has_value_int())
        {
            entries[0]->set_value_int(entries[1]->get_value_int());
        }

        if(entries[0]->has_value_double() && entries[1]->has_value_double())
        {
            entries[0]->set_value_double(entries[1]->get_value_double());
        }

        if(entries[0]->has_value_str() && entries[1]->has_value_str())
        {
            entries[0]->set_value_str(entries[1]->get_value_str());
        }

        if(entries[0]->has_value_bool() && entries[1]->has_value_bool())
        {
            entries[0]->set_value_bool(entries[1]->get_value_bool());
        }
    } 

    return entries;
}