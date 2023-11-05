#pragma once

#include <array>

#include "../../../Utils/Constants.hpp"

#include "../../../Entities/Entity.hpp"

/**
 * @brief x86-like ARN
 * 
 * Non executable code, aimed to be used later
*/
class FreeGenes : public Entity
{
protected:
    std::vector<int> genes;

public:
    using Entity::Entity;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;

    std::vector<int> get_genes();

    void set_genes(std::vector<int> genes);
};

typedef std::shared_ptr<FreeGenes> sp_freegenes;
