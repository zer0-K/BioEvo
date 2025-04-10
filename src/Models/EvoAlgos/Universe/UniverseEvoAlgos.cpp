#include "UniverseEvoAlgos.hpp"

#include <iostream>
#include <functional>

using std::placeholders::_1;
using std::placeholders::_2;

#include "../../../Utils/Constants.hpp"

#include "../X86Algo/FreeMolecules.hpp"

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

std::vector<int> UniverseEvoAlgos::get_free_molecules_at(int pos)
{
    // get the phenotypic body at given place, and replace with void
    if(pos>=0 && pos<places.size())
    {
        sp_entity entity = places[pos]->get_entity();

        if(entity->is_type(FREEGENES))
        {
            sp_free_molecules free_molecules = std::dynamic_pointer_cast<FreeMolecules>(entity);

            // replace free molecules by a void entity
            sp_entity_void entity_void = std::make_shared<EntityVoid>("void entity");
            entity_void->init();
            places[pos]->set_entity(entity_void);

            return free_molecules->get_phenotypic_body();
        }
    }

    return std::vector<int>(0);
}

bool UniverseEvoAlgos::write_free_molecules_at(int pos, std::vector<int> vals)
{
    // create free molecules with given values if place at given pos is empty
    if(UniverseEvoAlgos::is_empty(pos) && vals.size() > 0)
    {
        sp_entity new_entity = std::make_shared<Entity>("Entity " + std::to_string(pos));

        if(vals[0] == GGENESIS_ID)
        {
            sp_evox algo = std::make_shared<EvoX>("transcribed evox algo");
            algo->init();

            std::vector<int> phenotypic_body(vals.begin()+1, vals.end()-1);

            algo->set_phenotypic_body(phenotypic_body);

            // set data stack at 150
            algo->set_data_at(99, 150);

            new_entity = algo;
        }
        else
        {
            sp_free_molecules free_molecules = std::make_shared<FreeMolecules>("free molecules");
            free_molecules->init();

            free_molecules->set_phenotypic_body(vals);
            new_entity = free_molecules;
        }

        places[pos]->set_entity(new_entity);

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
            std::function<std::vector<int>(int)> f3 = std::bind(&UniverseEvoAlgos::get_free_molecules_at, this, _1);

            // write at place
            std::function<bool(int, std::vector<int>)> f4 = std::bind(&UniverseEvoAlgos::write_free_molecules_at, this, _1, _2);

            sp_x86algo x86algo = std::dynamic_pointer_cast<X86Algo>(entity);
            x86algo->init_external_functions(f1, f2, f3, f4);
        }
    }
}