#pragma once

#include "EntityOperationInt.hpp"

/// @brief add a code eater int value into another one
class EntityAddIntIn : public EntityOperationInt
{
public:
    using EntityOperationInt::EntityOperationInt;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityAddIntIn> sp_entity_addintin;
