#pragma once

#include "../../../../Entities/Entity.hpp"
#include "../../../../Entities/EntityInt.hpp"
#include "../../../../Entities/EntityBool.hpp"

class CodeEater;
typedef std::shared_ptr<CodeEater> sp_ce;

class CodeEater : public Entity
{
public:
    using Entity::Entity;

    /**
     * @brief list of code eaters that are executed sequentially 
     */
    std::vector<sp_entity> code;

    
    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;
};
