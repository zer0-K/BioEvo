#pragma once

#include "EntityOperationBoolean.hpp"

/**
 * @brief boolean not and gate
*/
class EntityNand : public EntityOperationBoolean
{
public:
    using EntityOperationBoolean::EntityOperationBoolean;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityNand> sp_entity_nand;

