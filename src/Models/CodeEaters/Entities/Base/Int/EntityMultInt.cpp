#include "EntityMultInt.hpp"

#include "../../../../../Utils/Constants.hpp"

void EntityMultInt::init()
{
    EntityOperationInt::init();

    type = TYPE_MULTINT;
    add_type(TYPE_MULTINT);
}

/**
 * @brief multiplication with 3 code eaters, the first one is the result
*/
std::vector<sp_entity> EntityMultInt::exec(std::vector<sp_entity> entries)
{
    if(entries.size() == 3)
    {
        if(entries[0]->has_value_int() && entries[1]->has_value_int()
            && entries[2]->has_value_int())
        {
            entries[0]->set_value_int(
                entries[1]->get_value_int() * entries[2]->get_value_int()
            );
        }
    }

    return entries;
}