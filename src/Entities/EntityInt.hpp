#pragma once

#include "EntityVoid.hpp"

class EntityInt : public EntityVoid
{
public:
    using EntityVoid::EntityVoid;
    
    void init();
};

typedef std::shared_ptr<EntityInt> sp_entity_int;
