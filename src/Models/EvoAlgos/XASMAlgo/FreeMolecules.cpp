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

std::vector<int> FreeMolecules::get_body()
{
    return body;
}

void FreeMolecules::set_body(std::vector<int> body)
{
    this->body = body;
}