#pragma once

#include "EntityOperationInt.hpp"

/// @brief divide 2 code eater int values into another one
class EntityDivInt : public EntityOperationInt
{
public:
    using EntityOperationInt::EntityOperationInt;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityDivInt> sp_entity_divint;

