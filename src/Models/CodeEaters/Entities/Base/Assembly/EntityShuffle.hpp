#pragma once

#include "../EntityOperation.hpp"

/**
 * @brief shuffle index entity
 * 
 * Should be called twice :
 *  - first, take the  
 */
class EntityShuffle : public EntityOperation
{
public:
    using EntityOperation::EntityOperation;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityShuffle> sp_entity_shuffle;
