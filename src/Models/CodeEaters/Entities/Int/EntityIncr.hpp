#pragma once

#include "EntityOperationInt.hpp"

class EntityIncr : public EntityOperationInt
{
public:
    using EntityOperationInt::EntityOperationInt;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityIncr> sp_entity_incr;
