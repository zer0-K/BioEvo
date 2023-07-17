#include "EntityAddIntIn.hpp"

#include "../../../../../Utils/Constants.hpp"

void EntityAddIntIn::init()
{
    EntityOperationInt::init();

    type = TYPE_ADDINTIN;
    add_type(TYPE_ADDINTIN);
}

/**
 * @brief addition with 2 code eaters, the first one is the result
*/
std::vector<sp_entity> EntityAddIntIn::exec(std::vector<sp_entity> entries)
{
    if(entries.size() == 2)
    {
        if(entries[0]->has_value_int() && entries[1]->has_value_int())
        {
            entries[0]->set_value_int(
                entries[0]->get_value_int() + entries[1]->get_value_int()
            );
        }
    }

    return entries;
}