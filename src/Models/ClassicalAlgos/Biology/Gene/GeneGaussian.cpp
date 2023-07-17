#include "GeneGaussian.hpp"

#include "../../../../Utils/Maths/RandomGen.hpp"

#include <string>

GeneGaussian::GeneGaussian(double mean_val, double std_dev_val, std::shared_ptr<Trait<double>> trait)
    :Gene::Gene(trait)
{
    mean = Trait<double>(mean_val);
    std_dev = Trait<double>(std_dev_val);
}

void GeneGaussian::drive()
{
    std::shared_ptr<Trait<double>> trait_as_double = std::dynamic_pointer_cast<Trait<double>>(trait_driven);

    double rnd_val = rand_gen::rand_normal(mean.get_value(), std_dev.get_value());

    trait_as_double->set_value(rnd_val); 
}

//---------- setters

void GeneGaussian::set_mean(double m)
{
    mean.set_value(m);
}

void GeneGaussian::set_std_dev(double s)
{
    std_dev.set_value(s);
}