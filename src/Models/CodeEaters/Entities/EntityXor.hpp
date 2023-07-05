#pragma once

#include "../../../Entities/Entity.hpp"

class EntityXor : public Entity
{
public:
    using Entity::Entity;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityXor> sp_entity_xor;

