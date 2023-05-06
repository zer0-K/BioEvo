#include "Gene.hpp"

Gene::Gene(double mean, double std_dev, sp_abstracttrait trait)
{
    this->mean = mean;
    this->std_dev = std_dev;
    this->trait_driven = trait;
}

//---------- getters

sp_abstracttrait Gene::get_trait()
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

std::string Gene::to_json()
{
    std::string res = "{";
    res += "'trait':" + this->trait_driven->to_json();
    res += ",'mean':" + std::to_string(this->mean);
    res += ",'std dev':" + std::to_string(this->std_dev); 
    return res;
}