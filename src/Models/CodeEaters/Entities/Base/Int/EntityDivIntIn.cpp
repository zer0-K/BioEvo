#include "EntityDivIntIn.hpp"

#include "../../../../../Utils/Constants.hpp"

void EntityDivIntIn::init()
{
    EntityOperationInt::init();

    type = TYPE_DIVINTIN;
    add_type(TYPE_DIVINTIN);
}

/**
 * @brief divide with 2 code eaters, the first one is the result
*/
std::vector<sp_entity> EntityDivIntIn::exec(std::vector<sp_entity> entries)
{
    if(entries.size() == 2)
    {
        if(entries[0]->has_value_int() && entries[1]->has_value_int())
        {
            entries[0]->set_value_int(
                entries[0]->get_value_int() / entries[1]->get_value_int()
            );
        }
    }

    return entries;
}