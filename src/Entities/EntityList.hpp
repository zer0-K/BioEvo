#pragma once

#include "Entity.hpp"

#include <vector>

class EntityList : public Entity
{
protected:
    std::vector<sp_entity> list;

public:
    using Entity::Entity;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityList> sp_entity_void;

