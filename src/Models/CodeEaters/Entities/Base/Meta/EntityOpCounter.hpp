#pragma once

#include "EntityMetaOp.hpp"

#include <map>

class EntityOpCounter : public EntityMetaOp
{
protected:
    std::map<std::string, int> counts;

public:
    using EntityMetaOp::EntityMetaOp;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;

    /**
     * @brief Add a count of the given type
     * 
     * For example, if counts["AND"] = 10 and this function is called
     * for type="AND", then counts["AND"] = 11
     * Set entry to 1 if didn't exist
    */
    void add_count(std::string type);

    /**
     * @brief give the count of the given type
    */
    int get_count(std::string type);
};

typedef std::shared_ptr<EntityOpCounter> sp_entity_opcounter;
