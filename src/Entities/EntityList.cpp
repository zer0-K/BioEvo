#include "EntityList.hpp"
#include "EntityVoid.hpp"

#include "../Utils/Constants.hpp"

void EntityList::init()
{
    type = TYPE_LIST;
    add_type(TYPE_LIST);
}

std::vector<sp_entity> EntityList::exec(std::vector<sp_entity> entries)
{
    return std::vector<sp_entity>(0);
}

void EntityList::append_entity(sp_entity entity)
{
    list.push_back(entity);
}

void EntityList::remove_entity_at(int pos)
{
    if(pos>=0 && pos<list.size())
    {
        for(int i=pos;i<list.size()-1;i++)
        {
            list[i] = list[i+1];
        }
        list.pop_back();
    }
    else
    {
        // error message ?
    }
}

sp_entity EntityList::get_entity_at(int pos)
{
    if(pos>=0 && pos<list.size())
    {
        return list[pos];
    }
    else
    {
        return std::make_shared<EntityVoid>("void");
    }
}