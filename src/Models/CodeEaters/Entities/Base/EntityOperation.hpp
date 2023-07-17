#pragma once

#include "../../../../Entities/Entity.hpp"

class EntityOperation : public Entity
{
public:
    using Entity::Entity;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;

    void increase_op_counter();
};

typedef std::shared_ptr<EntityOperation> sp_entity_op;
