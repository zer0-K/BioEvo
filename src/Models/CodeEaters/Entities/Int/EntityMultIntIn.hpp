#pragma once

#include "EntityOperationInt.hpp"

/// @brief multiply a code eater int value into another one
class EntityMultIntIn : public EntityOperationInt
{
public:
    using EntityOperationInt::EntityOperationInt;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityMultIntIn> sp_entity_multintin;
