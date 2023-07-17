#pragma once

#include "EntityOperationBoolean.hpp"

/**
 * @brief boolean and gate, in place
*/
class EntityAndIn : public EntityOperationBoolean
{
public:
    using EntityOperationBoolean::EntityOperationBoolean;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityAndIn> sp_entity_andin;

