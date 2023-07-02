#pragma once

#include "../../../Entities/Entity.hpp"

class LinearEntity : public Entity
{
public:
    LinearEntity(std::string entity_name);

    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<LinearEntity> sp_entity_linear;
