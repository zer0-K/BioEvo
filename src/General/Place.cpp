#include "Place.hpp"

Place::Place(sp_entity entity, int pos)
{
    this->entity = entity;
    position = pos;
}

void Place::set_entity(sp_entity new_entity)
{
    entity = new_entity;
}

sp_entity Place::get_entity()
{
    return entity;
}

int Place::get_position()
{
    return position;
}