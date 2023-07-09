#pragma once

#include "EntityOperationBoolean.hpp"

/**
 * @brief boolean id gate
*/
class EntityBoolId : public EntityOperationBoolean
{
public:
    using EntityOperationBoolean::EntityOperationBoolean;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityBoolId> sp_entity_boolid;
