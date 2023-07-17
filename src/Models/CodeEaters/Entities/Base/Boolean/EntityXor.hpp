#pragma once

#include "EntityOperationBoolean.hpp"

/**
 * @brief boolean xor gate
*/
class EntityXor : public EntityOperationBoolean
{
public:
    using EntityOperationBoolean::EntityOperationBoolean;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityXor> sp_entity_xor;

