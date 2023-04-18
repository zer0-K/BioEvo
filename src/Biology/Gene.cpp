#include "Gene.hpp"

Gene::Gene(double mean, double std_dev, AbstractTrait* trait)
{
    this->mean = mean;
    this->std_dev = std_dev;
    this->trait_driven = trait;
}

//---------- getters

AbstractTrait* Gene::get_trait()
{
    return this->trait_driven;
}

//---------- other

std::string Gene::to_string()
{
    std::string res = "";
    res += "trait : " + this->trait_driven->to_string() + " | ";
    res += "mean : " + std::to_string(this->mean) + " | ";
    res += "std dev : " + std::to_string(this->std_dev); 
    return res;
}