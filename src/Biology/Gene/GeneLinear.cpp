#include "GeneLinear.hpp"

#include"../../Utils/Math/RandomGen.hpp" 

GeneLinear::GeneLinear(double mean, double std_dev, std::shared_ptr<Trait<double>> trait)
    :Gene::Gene(mean, std_dev, trait)
{
    // do nothing here for the moment
}

void GeneLinear::drive()
{
    // random gaussian value
    double val_gen = rand_gen::rand_normal(this->mean, this->std_dev);

    // set value
    std::shared_ptr<Trait<double>> trait = std::dynamic_pointer_cast<Trait<double>>(
        this->trait_driven
    );
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