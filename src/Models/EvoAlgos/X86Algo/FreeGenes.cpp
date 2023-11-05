#include "FreeGenes.hpp"

void FreeGenes::init()
{
    type = FREEGENES;
    add_type(FREEGENES);
}

std::vector<sp_entity> FreeGenes::exec(std::vector<sp_entity> entries)
{
    // exec does nothing for free code
    return std::vector<sp_entity>(0);
}

std::vector<int> FreeGenes::get_genes()
{
    return genes;
}

void FreeGenes::set_genes(std::vector<int> genes)
{
    this->genes = genes;
}