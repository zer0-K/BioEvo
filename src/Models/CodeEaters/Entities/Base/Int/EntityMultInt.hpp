#pragma once

#include "EntityOperationInt.hpp"

/// @brief multiply 2 code eater int values into another one
class EntityMultInt : public EntityOperationInt
{
public:
    using EntityOperationInt::EntityOperationInt;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityMultInt> sp_entity_multint;
