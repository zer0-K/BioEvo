#pragma once

#include "EntityOperationBoolean.hpp"

/**
 * @brief boolean not gate
*/
class EntityUnaryNot : public EntityOperationBoolean
{
public:
    using EntityOperationBoolean::EntityOperationBoolean;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityUnaryNot> sp_entity_unot;

