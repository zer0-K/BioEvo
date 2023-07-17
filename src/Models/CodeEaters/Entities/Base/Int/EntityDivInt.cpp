#include "EntityDivInt.hpp"

#include "../../../../../Utils/Constants.hpp"

void EntityDivInt::init()
{
    EntityOperationInt::init();

    type = TYPE_DIVINT;
    add_type(TYPE_DIVINT);
}

/**
 * @brief divide with 3 code eaters, the first one is the result
*/
std::vector<sp_entity> EntityDivInt::exec(std::vector<sp_entity> entries)
{
    if(entries.size() == 3)
    {
        if(entries[0]->has_value_int() && entries[1]->has_value_int()
            && entries[2]->has_value_int())
        {
            entries[0]->set_value_int(
                entries[1]->get_value_int() / entries[2]->get_value_int()
            );
        }
    }

    return entries;
}