#include "Gene.hpp"

#include <string>

Gene::Gene(double mean_val, double std_dev_val, sp_abstracttrait trait)
{
    mean = Trait<double>(mean);
    std_dev = Trait<double>(std_dev);
    trait_driven = trait;
}

//---------- getters

sp_abstracttrait Gene::get_trait()
{
    return this->trait_driven;
}

//---------- setters

void Gene::set_mean(double m)
{
    mean.set_value(m);
}

void Gene::set_std_dev(double s)
{
    std_dev.set_value(s);
}

//---------- other

std::string Gene::to_string()
{
    std::string res = "";
    res += "trait : " + trait_driven->to_string() + " | ";
    res += "mean : " + std::to_string(mean.get_value()) + " | ";
    res += "std dev : " + std::to_string(std_dev.get_value()); 
    return res;
}
