#pragma once

#include "EntityOperationBoolean.hpp"

/**
 * @brief boolean or gate
*/
class EntityOr : public EntityOperationBoolean
{
public:
    using EntityOperationBoolean::EntityOperationBoolean;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityOr> sp_entity_or;
