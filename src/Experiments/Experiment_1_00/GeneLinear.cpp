#include "GeneLinear.hpp"

#include"../../Utils/Math/RandomGen.hpp" 

GeneLinear::GeneLinear(double mean, double std_dev, Trait<double>* trait)
    :Gene::Gene(mean, std_dev, (AbstractTrait*) trait)
{
    // do nothing here for the moment
}

void GeneLinear::drive()
{
    // set a random gaussian value
    double val_gen = rand_gen::rand_normal(this->mean, this->std_dev);
    Trait<double>* trait = (Trait<double>*) this->trait_driven;
    trait->set_value(val_gen);
}

//---------- other

std::string GeneLinear::to_string()
{
    std::string res = "";
    res += Gene::to_string();
    return res;
}

std::string GeneLinear::to_json()
{
    std::string res = "";
    res += Gene::to_json();
    return res;
}