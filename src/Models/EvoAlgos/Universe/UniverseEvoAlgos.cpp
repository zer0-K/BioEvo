#include "UniverseEvoAlgos.hpp"

#include <iostream>

#include "../../../Utils/Constants.hpp"

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

void UniverseEvoAlgos::update_flows(sp_entity entity)
{
    if(entity->is_type(X86_ALGO))
    {
        // get algo's output flow
        sp_x86algo algo = std::dynamic_pointer_cast<X86Algo>(entity);
        std::vector<std::array<int,2>> output_flow = algo->get_output_flows();

        // connect ouput flow
        for(int place_index=0;place_index<places.size();place_index++)
        {
            sp_entity entity_to_connect = places[place_index]->get_entity();

            // connects only to x86 algos
            if(entity_to_connect->is_type(X86_ALGO))
            {
                sp_x86algo algo_to_connect = std::dynamic_pointer_cast<X86Algo>(entity_to_connect);

                // connect if requirements are satisfied
                if(do_connect_flows(output_flow, algo_to_connect))
                {
                    algo->add_connected_out(place_index);
                }
            }
        }
    }
}

bool UniverseEvoAlgos::do_connect_flows(std::vector<std::array<int,2>> output_flow, sp_x86algo entity_to_connect)
{
    std::vector<std::array<int,2>> input_flow = entity_to_connect->get_input_flows();

    // connect if at least one key-value matches 
    for(int i=0;i<output_flow.size();i++)
    {
        for(int j=0;j<input_flow.size();j++)
        {
            if(output_flow[i][0] == input_flow[j][0]
                && output_flow[i][1] == input_flow[j][1])
            {
                return true;
            }
        }
    }

    return false;
}