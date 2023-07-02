#pragma once

#include "Entity.hpp"

class VoidEntity : public Entity
{
public:
    VoidEntity(std::string entity_name);
    VoidEntity(std::string entity_name, int val);
    VoidEntity(std::string entity_name, double val);
    VoidEntity(std::string entity_name, std::string val);
    VoidEntity(std::string entity_name, bool val);

    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<VoidEntity> sp_entity_void;
