#pragma once

#include "EntityOperationInt.hpp"

/// @brief add 2 code eater int values into another one
class EntityAddInt : public EntityOperationInt
{
public:
    using EntityOperationInt::EntityOperationInt;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityAddInt> sp_entity_addint;
