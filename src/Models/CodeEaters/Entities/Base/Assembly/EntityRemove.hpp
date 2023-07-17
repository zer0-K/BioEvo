#pragma once

#include "../EntityOperation.hpp"

/**
 * @brief entity to remove code eaters
 * 
 * Takes as param anything and should return a list of 
 * int (entities), the code eaters at these places will be removed
*/
class EntityRemove : public EntityOperation
{
public:
    using EntityOperation::EntityOperation;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityRemove> sp_entity_shuffle;
