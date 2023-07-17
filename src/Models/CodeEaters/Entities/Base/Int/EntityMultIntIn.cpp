#include "EntityMultIntIn.hpp"

#include "../../../../../Utils/Constants.hpp"

void EntityMultIntIn::init()
{
    EntityOperationInt::init();

    type = TYPE_MULTINTIN;
    add_type(TYPE_MULTINTIN);
}

/**
 * @brief multiplication with 2 code eaters, the first one is the result
*/
std::vector<sp_entity> EntityMultIntIn::exec(std::vector<sp_entity> entries)
{
    if(entries.size() == 2)
    {
        if(entries[0]->has_value_int() && entries[1]->has_value_int())
        {
            entries[0]->set_value_int(
                entries[0]->get_value_int() * entries[1]->get_value_int()
            );
        }
    }

    return entries;
}