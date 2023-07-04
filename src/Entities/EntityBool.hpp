#pragma once

#include "EntityVoid.hpp"

class EntityBool : public EntityVoid
{
public:
    using EntityVoid::EntityVoid;
    
    void init();
};

typedef std::shared_ptr<EntityBool> sp_entity_bool;
