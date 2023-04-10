#include "EnvironmentLinear.hpp"

EnvironmentLinear::EnvironmentLinear(std::string name, int dimension, double* w, double b)
    :Environment::Environment(name)
{
    this->dimension = dimension;
    this->w = w;
    this->b = b;
}

void EnvironmentLinear::evolve()
{

}