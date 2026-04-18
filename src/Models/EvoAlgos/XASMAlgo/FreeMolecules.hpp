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
    std::vector<int> body;

public:
    using Entity::Entity;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;

    std::vector<int> get_body();

    void set_body(std::vector<int> body);
};

typedef std::shared_ptr<FreeMolecules> sp_free_molecules;
