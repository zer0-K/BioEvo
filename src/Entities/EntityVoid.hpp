#pragma once

#include "Entity.hpp"

class EntityVoid : public Entity
{
public:
    using Entity::Entity;
    
    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityVoid> sp_entity_void;
