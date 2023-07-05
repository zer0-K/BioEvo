#pragma once

#include "../../../Entities/Entity.hpp"

class EntityAnd : public Entity
{
public:
    using Entity::Entity;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityAnd> sp_entity_and;

