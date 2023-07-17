#pragma once

#include "EntityOperationBoolean.hpp"

/**
 * @brief boolean not or gate, in place
*/
class EntityNorIn : public EntityOperationBoolean
{
public:
    using EntityOperationBoolean::EntityOperationBoolean;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityNorIn> sp_entity_norin;
