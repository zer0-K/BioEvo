#pragma once

#include "../EntityOperation.hpp"

/**
 * @brief entity to remove code eaters
 * 
 * Takes as param anything and should return a single code eater that will
 * be added at the index corresponding to the int value of the insert code eater
*/
class EntityInsert : public EntityOperation
{
public:
    using EntityOperation::EntityOperation;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityInsert> sp_entity_shuffle;

