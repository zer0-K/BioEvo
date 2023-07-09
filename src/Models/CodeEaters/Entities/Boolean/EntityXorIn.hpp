#pragma once

#include "EntityOperationBoolean.hpp"

/**
 * @brief boolean xor gate, in place
*/
class EntityXorIn : public EntityOperationBoolean
{
public:
    using EntityOperationBoolean::EntityOperationBoolean;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityXorIn> sp_entity_xorin;

