#pragma once

#include "EntityOperationBoolean.hpp"

/**
 * @brief boolean id gate
*/
class EntityUnaryId : public EntityOperationBoolean
{
public:
    using EntityOperationBoolean::EntityOperationBoolean;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityUnaryId> sp_entity_uid;
