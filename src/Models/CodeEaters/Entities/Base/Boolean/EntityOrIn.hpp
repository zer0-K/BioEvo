#pragma once

#include "EntityOperationBoolean.hpp"

/**
 * @brief boolean or gate, in place
*/
class EntityOrIn : public EntityOperationBoolean
{
public:
    using EntityOperationBoolean::EntityOperationBoolean;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityOrIn> sp_entity_orin;
