#include "Universe.hpp"

#include "../General/VoidEntity.hpp"

Universe::Universe(int size_universe, std::string name)
{
    this->name = name;

    places = std::vector<sp_place>(size_universe);

    for(int i=0; i<size_universe; i++)
    {
        sp_entity entity = std::make_shared<VoidEntity>("entity void " + std::to_string(i));

        sp_place place = std::make_shared<Place>(entity, i);

        places[i] = place;
    }
}

Universe::Universe(std::string name, std::vector<sp_place> places)
{
    this->name = name;
    this->places = places;
}

Universe::Universe(std::string name, std::vector<sp_place> places, std::vector<sp_place> meta_places)
{
    this->name = name;
    this->places = places;
    this->meta_places = meta_places;
}

void Universe::exec()
{
    sp_entity entity;
    int place_index=0;

    for(int i=0;i<places.size();i++)
    {
        entity = places[i]->get_entity();
        place_index = entity->get_working_place_index();

        entity = entity->exec(places[place_index]->get_entity())[0];

        places[place_index]->set_entity(entity);
    }
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
