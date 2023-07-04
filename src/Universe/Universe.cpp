#include "Universe.hpp"

#include "../Utils/Constants.hpp"
#include "../Entities/EntityVoid.hpp"

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

Universe::Universe(std::string name, std::vector<sp_place> places, std::vector<sp_place> meta_places)
{
    this->name = name;
    this->places = places;
    this->meta_places = meta_places;
}

void Universe::exec()
{
    sp_entity working_entity;
    sp_entity handled_entity;
    sp_entity result_entity;
    sp_entity_void void_entity;
    int place_index=0;

    for(int i=0;i<places.size();i++)
    {
        // get working entity and index of where it want to work on
        working_entity = places[i]->get_entity();
        place_index = working_entity->get_working_place_index();

        // get entity to work on and set a void entity there
        handled_entity = places[place_index]->get_entity();
        void_entity = std::make_shared<EntityVoid>("void entity");
        void_entity->init();
        places[place_index]->set_entity(void_entity);


        // get result and apply
        result_entity = result_entity->exec(places[place_index]->get_entity())[0];
        if( places[place_index]->get_entity()->get_type() == TYPE_VOID )
        {
            places[place_index]->set_entity(result_entity);
        }
        else
        {
            // nothing
            // will handle this later for concurrency stuff
        } 
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
