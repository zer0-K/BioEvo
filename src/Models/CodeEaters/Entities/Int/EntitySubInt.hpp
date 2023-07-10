#pragma once

#include "EntityOperationInt.hpp"

/// @brief substract 2 code eater int values into another one
class EntitySubInt : public EntityOperationInt
{
public:
    using EntityOperationInt::EntityOperationInt;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntitySubInt> sp_entity_subint;
