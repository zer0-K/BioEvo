#include "UniverseEvoXCustomNeighborhood.hpp"

#include <iostream>

using namespace std::placeholders;

#include "CustomNeighborhoods.hpp"

UniverseEvoXCustomNeighborhood::UniverseEvoXCustomNeighborhood(int nbrows, int nbcols, std::string name)
    :UniverseEvoAlgos::UniverseEvoAlgos(nbrows*nbcols, name)
{
    nb_cols = nbcols;
    nb_rows = nbrows;
}

UniverseEvoXCustomNeighborhood::UniverseEvoXCustomNeighborhood(int nbrows, int nbcols, 
        std::vector<sp_evox> algos, std::vector<std::array<int, 2>> positions, std::string name)
    :UniverseEvoAlgos::UniverseEvoAlgos(nbrows*nbcols, name)
{
    nb_cols = nbcols;
    nb_rows = nbrows;

    if(positions.size() != algos.size()) 
    {
        std::cout << "\t\tError : " 
            << algos.size() <<  " algos given, but "
            << positions.size() << " positions given."
            << std::endl;
    }

    for(int i=0;i<algos.size();i++)
    {
        std::array<int, 2> pos = positions[i];

        if(pos[0]<0 || pos[0]>=nbrows || pos[1]<0 || pos[1]>=nbcols) 
        {
            std::cout << "\t\tError : universe dimensions are " 
                << nbrows << "x"
                << nbcols << ", cannot place algo at ("
                << pos[0] <<  ","
                << pos[1] << ")."
                << std::endl;
        }
        else
        {
            places[pos[0]*nbcols+pos[1]]->set_entity(algos[i]);
        }
    }
}

void UniverseEvoXCustomNeighborhood::exec()
{
    /**
     * Goes through the places one by one and execute the 
     * algo at the current place
     * If the algo's out is connected to another's algo's in,
     * simply sets the one's input with the first's output, it will be executed later
     */
    sp_entity current_entity;
    std::vector<int> connected_entities_indices;
    sp_entity connected_entity;

    for(int i=0;i<places.size();i++)
    {
        // get current entity
        current_exec_pos = i;
        current_entity = places[i]->get_entity();

        if(current_entity->is_type(X86_ALGO))
        {
            sp_x86algo algo = std::dynamic_pointer_cast<X86Algo>(current_entity);
            neighborhood_size = algo->get_neighborhood_size();
        }

        // execute and update flows
        current_entity->exec();
    }

}

bool UniverseEvoXCustomNeighborhood::is_empty(int pos)
{
    int absolute_pos = get_pos_from_neighborhood_coords(current_exec_pos, 
        pos, 
        neighborhood_size,
        nb_rows,
        nb_cols
    );

    if(absolute_pos<0)
    {
        return false;
    }

    return UniverseEvoAlgos::is_empty(absolute_pos);
}

std::vector<int> UniverseEvoXCustomNeighborhood::get_freegenes_at(int pos)
{
    int absolute_pos = get_pos_from_neighborhood_coords(current_exec_pos, 
        pos, 
        neighborhood_size,
        nb_rows,
        nb_cols
    );

    if(absolute_pos<0)
    {
        return std::vector<int>(0);
    }

    return UniverseEvoAlgos::get_freegenes_at(absolute_pos);
}

bool UniverseEvoXCustomNeighborhood::write_freegenes_at(int pos, std::vector<int> vals)
{
    int absolute_pos = get_pos_from_neighborhood_coords(current_exec_pos, 
        pos, 
        neighborhood_size,
        nb_rows,
        nb_cols
    );

    if(absolute_pos<0)
    {
        return false;
    }

    return UniverseEvoAlgos::write_freegenes_at(absolute_pos, vals);
}

void UniverseEvoXCustomNeighborhood::link_universe_functions_to_individuals(neighborhoodType nt, int params[])
{
    neighborhood_size = params[0];
    int nb_cells_neighborhood = 0;

    switch(nt) 
    {
        case neighborhoodType::MOORE:
            get_pos_from_neighborhood_coords = std::bind(&get_pos_from_von_neumann_neighborhood, _1, _2, _3, _4, _5);
            nb_cells_neighborhood = nb_of_cells_von_neumann(neighborhood_size);
            break;
        case neighborhoodType::VON_NEUMANN:
            get_pos_from_neighborhood_coords = std::bind(&get_pos_from_von_neumann_neighborhood, _1, _2, _3, _4, _5);
            nb_cells_neighborhood = nb_of_cells_von_neumann(neighborhood_size);
            break;
        default:
            get_pos_from_neighborhood_coords = std::bind(&get_pos_from_von_neumann_neighborhood, _1, _2, _3, _4, _5);
            nb_cells_neighborhood = nb_of_cells_von_neumann(neighborhood_size);
            break;
    }

    // for all X86 entities, set their external functions (get universe size,...)
    for(int i=0;i<places.size();i++)
    {
        sp_entity entity = places[i]->get_entity();

        if(entity->is_type(X86_ALGO))
        {
            sp_x86algo algo = std::dynamic_pointer_cast<X86Algo>(entity);
            algo->set_neighborhood_size(neighborhood_size);

            // we force universe size to be the nb of cells in the neighborhood
            // so that an individual cannot reach smth outside of its neighborhood 
            std::function<int()> f1 = [nb_cells_neighborhood](){ return nb_cells_neighborhood; };

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
