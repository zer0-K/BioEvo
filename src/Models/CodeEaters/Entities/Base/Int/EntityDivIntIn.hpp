#pragma once

#include "EntityOperationInt.hpp"

/// @brief divide a code eater int value into another one
class EntityDivIntIn : public EntityOperationInt
{
public:
    using EntityOperationInt::EntityOperationInt;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityDivIntIn> sp_entity_divintin;

