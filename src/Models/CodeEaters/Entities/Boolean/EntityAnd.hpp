#pragma once

#include "EntityOperationBoolean.hpp"

/**
 * @brief boolean and gate
*/
class EntityAnd : public EntityOperationBoolean
{
public:
    using EntityOperationBoolean::EntityOperationBoolean;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityAnd> sp_entity_and;

