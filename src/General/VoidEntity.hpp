#pragma once

#include "Entity.hpp"

class VoidEntity : public Entity
{
public:
    VoidEntity(std::string entity_name);

    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<VoidEntity> sp_entity_void;
