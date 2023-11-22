#include "UniverseEvoAlgos.hpp"

#include <iostream>
#include <functional>

using std::placeholders::_1;
using std::placeholders::_2;

#include "../../../Utils/Constants.hpp"

#include "../X86Algo/FreeGenes.hpp"

UniverseEvoAlgos::UniverseEvoAlgos(int size, std::string name)
    :Universe::Universe(size, name)
{
}

UniverseEvoAlgos::UniverseEvoAlgos(std::vector<sp_x86algo> algos, std::string name)
    :Universe::Universe(algos.size(), name)
{
    for(int i=0;i<algos.size();i++)
    {
        places[i]->set_entity(algos[i]);
    }
}

UniverseEvoAlgos::UniverseEvoAlgos(std::vector<sp_evox> algos, std::string name)
    :Universe::Universe(algos.size(), name)
{
    for(int i=0;i<algos.size();i++)
    {
        places[i]->set_entity(algos[i]);
    }
}

void UniverseEvoAlgos::exec()
{
    Universe::exec();
}

bool UniverseEvoAlgos::is_empty(int pos)
{
    if(pos>=0 && pos<places.size())
    {
        sp_entity entity = places[pos]->get_entity();
        return entity->is_type(TYPE_VOID);
    }

    return false;
}

std::vector<int> UniverseEvoAlgos::get_freegenes_at(int pos)
{
    // get the genes at given place, and replace with void
    if(pos>=0 && pos<places.size())
    {
        sp_entity entity = places[pos]->get_entity();

        if(entity->is_type(FREEGENES))
        {
            sp_freegenes freegenes = std::dynamic_pointer_cast<FreeGenes>(entity);

            // replace free genes by a void entity
            sp_entity_void entity_void = std::make_shared<EntityVoid>("void entity");
            entity_void->init();
            places[pos]->set_entity(entity_void);

            return freegenes->get_genes();
        }
    }

    return std::vector<int>(0);
}

bool UniverseEvoAlgos::write_freegenes_at(int pos, std::vector<int> vals)
{
    // create free genes with given values if place at given pos is empty
    if(is_empty(pos))
    {
        sp_freegenes freegenes = std::make_shared<FreeGenes>("free genes");
        freegenes->init();

        freegenes->set_genes(vals);

        places[pos]->set_entity(freegenes);

        return true;
    }

    return false;
}

void UniverseEvoAlgos::link_universe_functions_to_individuals()
{
    // for all X86 entities, set their external functions (get universe size,...)
    for(int i=0;i<places.size();i++)
    {
        sp_entity entity = places[i]->get_entity();

        if(entity->is_type(X86_ALGO))
        {
            // universe size
            std::function<int()> f1 = std::bind(&Universe::get_universe_size, this);

            // is empty
            std::function<bool(int)> f2 = std::bind(&UniverseEvoAlgos::is_empty, this, _1);

            // read at place
            std::function<std::vector<int>(int)> f3 = std::bind(&UniverseEvoAlgos::get_freegenes_at, this, _1);

            // write at place
            std::function<bool(int, std::vector<int>)> f4 = std::bind(&UniverseEvoAlgos::write_freegenes_at, this, _1, _2);

            sp_x86algo x86algo = std::dynamic_pointer_cast<X86Algo>(entity);
            x86algo->init_external_functions(f1, f2, f3, f4);
        }
    }
}