#pragma once

#include "EntityOperationBoolean.hpp"

/**
 * @brief boolean not and gate, in place
*/
class EntityNandIn : public EntityOperationBoolean
{
public:
    using EntityOperationBoolean::EntityOperationBoolean;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityNandIn> sp_entity_nandin;

