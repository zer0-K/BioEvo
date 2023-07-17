#pragma once

#include "EntityOperationBoolean.hpp"

/**
 * @brief boolean not xor gate, in place
*/
class EntityNxorIn : public EntityOperationBoolean
{
public:
    using EntityOperationBoolean::EntityOperationBoolean;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityNxorIn> sp_entity_nxorin;

