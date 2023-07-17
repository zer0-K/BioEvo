#include "DataGeneratorLinear.hpp"

#include <iostream>

#include "../../../../Utils/Maths/RandomGen.hpp"

DataGeneratorLinear::DataGeneratorLinear()
{
    int mode;

    std::cout << "Initialiazing data generator. Choose mode : " << std::endl;
    std::cout << "\t0 - auto" << std::endl;
    std::cout << "\t1- custom" << std::endl;

    std::cin >> mode;

    switch(mode)
    {
        case 0:
            init_default();
            break;
        case 1:
            init_custom();
            break;
        default:
            init_default();
            break;
    }

}

void DataGeneratorLinear::init_default()
{
    coeffs = {  1.0, 3.14, -8.1, 0.44   };

    std::cout << "Default linear model generator : "    << std::endl;
    print_model();
}

void DataGeneratorLinear::init_custom()
{
    int dim = 0;

    while(dim<1 || dim > 1000)
    {
        std::cout << "Enter linear model dimension (min:1, max : 999)" << std::endl;
        std::cin >> dim;
    }

    coeffs = std::vector<double>(dim);

    for(int i=0; i<dim; i++)
    {
        std::cout << "Enter coeff " << i << " (double) : ";
        std::cin >> coeffs[i];
    }

    std::cout << "Created generator for linear model : "    << std::endl;
    print_model();
}

std::vector<double> DataGeneratorLinear::generate_single_x(int seed)
{
    auto x = std::vector<double>(coeffs.size());

    for(int i=0; i<x.size(); i++)
    {
        x[i] = rand_gen::rand_double(-100, 100);
    }

    return x;
}

double DataGeneratorLinear::compute(std::vector<double> x)
{
    double f_x = 0;

    if(x.size() == coeffs.size())
    {
        for(int i=0; i<x.size();i++)
        {
            f_x += x[i] * coeffs[i];
        }
    }

    return f_x;
}

void DataGeneratorLinear::print_model()
{
    std::cout << "\t- dim : "       << coeffs.size()    << std::endl;

    std::cout << "\t- coeffs : ";
    for(int i=0;i<coeffs.size();i++)
        std::cout << coeffs[i] << " ";
    std::cout << std::endl;

}