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

std::vector<int> FreeMolecules::get_molecular_body()
{
    return molecular_body;
}

void FreeMolecules::set_molecular_body(std::vector<int> molecular_body)
{
    this->molecular_body = molecular_body;
}