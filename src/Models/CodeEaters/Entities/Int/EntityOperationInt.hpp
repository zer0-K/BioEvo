#pragma once

#include "../EntityOperation.hpp"

class EntityOperationInt : public EntityOperation
{
public:
    using EntityOperation::EntityOperation;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityOperationInt> sp_entity_op_int;

