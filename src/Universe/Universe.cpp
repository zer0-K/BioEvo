#include "Universe.hpp"

#include "../Utils/Constants.hpp"
#include "../Entities/EntityVoid.hpp"
#include <array>

Universe::Universe(int size_universe, std::string name)
{
    this->name = name;

    places = std::vector<sp_place>(size_universe);

    for(int i=0; i<size_universe; i++)
    {
        sp_entity entity = std::make_shared<EntityVoid>("entity void " + std::to_string(i));
        entity->init();

        sp_place place = std::make_shared<Place>(entity, i);

        places[i] = place;
    }
}

Universe::Universe(std::string name, std::vector<sp_place> places)
{
    this->name = name;
    this->places = places;
}

Universe::Universe(std::string name, std::vector<sp_entity> entities)
{
    this->name = name;

    // create places for the corresponding entities
    std::vector<sp_place> new_places(entities.size());
    for(int i=0;i<entities.size();i++)
    {
        new_places[i] = std::make_shared<Place>(entities[i], i);
    }

    this->places = new_places;
}

Universe::Universe(std::string name, std::vector<sp_place> places, std::vector<sp_place> meta_places)
{
    this->name = name;
    this->places = places;
    this->meta_places = meta_places;
}

Universe::Universe(std::string name, std::vector<sp_entity> entities, std::vector<sp_entity> meta_entities)
{
    this->name = name;

    std::vector<sp_place> new_places(entities.size());
    std::vector<sp_place> new_meta_places(meta_entities.size());

    for(int i=0;i<entities.size();i++)
        new_places[i] = std::make_shared<Place>(entities[i], i);

    for(int i=0;i<meta_entities.size();i++)
        new_meta_places[i] = std::make_shared<Place>(meta_entities[i], i);

    this->places = new_places;
    this->meta_places = new_meta_places;
}


void Universe::exec()
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
        current_entity = places[i]->get_entity();

        // execute and update flows
        current_entity->exec();
        update_flows(current_entity);

        // set in of connected entities with current out
        connected_entities_indices = current_entity->get_connected_outs();
        for(int j=0;j<connected_entities_indices.size();j++)
        {
            // get entity at given place
            int conn_index = connected_entities_indices[j];
            if(conn_index>=0 && conn_index<places.size())
            {
                connected_entity = places[conn_index]->get_entity();

                // set its input
                connected_entity->set_input(current_entity->get_output());
            }
        }
    }
}

void Universe::update_flows(sp_entity entity)
{
    // does nothing in this (parent) class
}

std::vector<std::array<int,2>> Universe::get_place_graph()
{
    std::vector<std::array<int,2>> place_graph(0);

    for(int i=0;i<places.size();i++)
    {
        // get output stream of entity at place i
        std::vector<int> outs_connected = places[i]->get_entity()->get_connected_outs();

        for(int j=0;j<outs_connected.size();j++)
        {
            // means that i connects its out to another one
            place_graph.push_back( { i, outs_connected[j] } );
        }
    }

    return place_graph;
}

//-------------------- getters

std::string Universe::get_name()
{
    return name;
}

std::vector<sp_place> Universe::get_places()
{
    return places;
}

std::vector<sp_place> Universe::get_meta_places()
{
    return meta_places;
}
