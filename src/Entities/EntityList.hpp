#pragma once

#include "Entity.hpp"

#include <vector>

class EntityList : public Entity
{
protected:
    std::vector<sp_entity> list;

public:
    EntityList(std::string entity_name);
    EntityList(std::string entity_name, int val_int);
    EntityList(std::string entity_name, double val);
    EntityList(std::string entity_name, std::string val);
    EntityList(std::string entity_name, bool val);

    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};

typedef std::shared_ptr<EntityList> sp_entity_void;

