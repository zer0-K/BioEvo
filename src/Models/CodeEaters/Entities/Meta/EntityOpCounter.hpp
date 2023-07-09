#pragma once

#include "EntityMeta.hpp"

#include <map>

class EntityOpCounter : public EntityMeta
{
public:
    /**
     * Counters for the operations
     * For example, if 10 AND code eaters are executed (or one 
     * AND code eater is executed 10 times), the entry "TYPE_AND"
     * should be equal to 10
    */
    std::map<std::string, int> counts;

    using EntityMeta::EntityMeta;

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
