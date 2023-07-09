#include "EntityIncr.hpp"

#include "../../../../Utils/Constants.hpp"

void EntityIncr::init()
{
    EntityOperationInt::init();

    type = TYPE_INCR;
    add_type(TYPE_INCR);
}

/**
 * @brief increment all entries that are int entities
*/
std::vector<sp_entity> EntityIncr::exec(std::vector<sp_entity> entries)
{
    // increment all entries
    for(int i=0;i<entries.size();i++)
    {
        if(entries[i]->has_value_int())
        {
            entries[i]->set_value_int(
                entries[i]->get_value_int()+1
            );
        }
    }

    return entries;
}