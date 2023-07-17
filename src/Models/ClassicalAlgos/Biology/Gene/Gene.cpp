#include "Gene.hpp"

#include <string>

Gene::Gene(sp_abstracttrait trait)
{
   trait_driven = trait;
}

//---------- getters

sp_abstracttrait Gene::get_trait()
{
    return this->trait_driven;
}
