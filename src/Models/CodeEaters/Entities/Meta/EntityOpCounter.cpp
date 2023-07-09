#include "EntityOpCounter.hpp"

#include "../../../../Utils/Constants.hpp"

void EntityOpCounter::init()
{
    type = TYPE_OP_COUNTER;
    add_type(TYPE_OP_COUNTER);
}

std::vector<sp_entity> EntityOpCounter::exec(std::vector<sp_entity> entries)
{
    // does nothing

    return entries;
}

void EntityOpCounter::add_count(std::string type)
{
    if(counts.find(type) == counts.end())
    {
        counts[type] = 1;
    }
    else
    {
        // increment the count 
        counts[type]++;
    }
}

int EntityOpCounter::get_count(std::string type)
{
    if(counts.find(type) == counts.end())
    {
        return 0;
    }
    else
    {
        return counts[type];
    }   
}