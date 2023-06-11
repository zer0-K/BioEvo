#pragma once

#include <vector>
#include <string>
#include <memory>

class Entity;
typedef std::shared_ptr<Entity> sp_entity;

class Entity
{
protected:
    std::string name;
    std::string type;

    int working_place_index;

public:

    Entity(std::string entity_name, std::string entity_type);

    virtual std::vector<sp_entity> exec(std::vector<sp_entity> entries) { return std::vector<sp_entity>(0); };
    std::vector<sp_entity> exec(sp_entity entry);

    std::string get_name();
    std::string get_type();
    int get_working_place_index();
};