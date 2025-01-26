#include "ClassicalIndividual.hpp"

#include "../../../Utils/Constants.hpp"

void ClassicalIndividual::init()
{
    //Entity::init();

    type = CA_INDIVIDUAL;
    add_type(CA_INDIVIDUAL);
}

std::vector<sp_entity> ClassicalIndividual::exec(std::vector<sp_entity> entries)
{
    // does nothing

    return entries;
}

void ClassicalIndividual::update_coeffs()
{
    for(int i=0;i<phenotypic_body.size();i++)
    {
        phenotypic_body[i]->drive();
    }
}