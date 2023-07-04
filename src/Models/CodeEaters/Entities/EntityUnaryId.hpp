#pragma once

#include "../../../Entities/Entity.hpp"

class EntityUnaryId : public Entity
{
public:
    using Entity::Entity;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityUnaryId> sp_entity_uid;
