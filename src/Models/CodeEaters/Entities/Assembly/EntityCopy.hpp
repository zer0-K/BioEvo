#pragma once

#include "../EntityOperation.hpp"

class EntityCopy : public EntityOperation
{
public:
    using EntityOperation::EntityOperation;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityCopy> sp_entity_copy;

