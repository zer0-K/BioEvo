#pragma once

#include "EntityOperationBoolean.hpp"

/**
 * @brief boolean not or gate
*/
class EntityNor : public EntityOperationBoolean
{
public:
    using EntityOperationBoolean::EntityOperationBoolean;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityNor> sp_entity_nor;
