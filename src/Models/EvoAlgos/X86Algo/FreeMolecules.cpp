#include "FreeMolecules.hpp"

void FreeMolecules::init()
{
    type = FREEGENES;
    add_type(FREEGENES);
}

std::vector<sp_entity> FreeMolecules::exec(std::vector<sp_entity> entries)
{
    // exec does nothing for free code
    return std::vector<sp_entity>(0);
}

std::vector<int> FreeMolecules::get_phenotypic_body()
{
    return phenotypic_body;
}

void FreeMolecules::set_phenotypic_body(std::vector<int> phenotypic_body)
{
    this->phenotypic_body = phenotypic_body;
}