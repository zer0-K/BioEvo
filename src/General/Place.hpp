#pragma once

#include "../Entities/Entity.hpp"

class Place;
typedef std::shared_ptr<Place> sp_place;

class Place
{
protected:
    sp_entity entity;
    int position;

public:
    Place(sp_entity entity, int pos);

    void set_entity(sp_entity new_entity);

    sp_entity get_entity();
    int get_position();
};