#pragma once

#include "EntityOperationInt.hpp"

/// @brief substract a code eater int value into another one
class EntitySubIntIn : public EntityOperationInt
{
public:
    using EntityOperationInt::EntityOperationInt;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntitySubIntIn> sp_entity_subintin;
