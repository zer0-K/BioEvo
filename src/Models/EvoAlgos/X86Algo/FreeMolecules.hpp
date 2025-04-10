#pragma once

#include <array>

#include "../../../Utils/Constants.hpp"

#include "../../../Entities/Entity.hpp"

/**
 * @brief x86-like ARN
 * 
 * Non executable code, aimed to be used later
*/
class FreeMolecules : public Entity
{
protected:
    std::vector<int> phenotypic_body;

public:
    using Entity::Entity;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;

    std::vector<int> get_phenotypic_body();

    void set_phenotypic_body(std::vector<int> phenotypic_body);
};

typedef std::shared_ptr<FreeMolecules> sp_free_molecules;
