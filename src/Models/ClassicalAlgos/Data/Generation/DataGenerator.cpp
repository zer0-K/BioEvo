#include "DataGenerator.hpp"

#include <iostream>

std::vector<sp_classical_data_test> DataGenerator::generate_test(int n)
{
    auto gendata = std::vector<sp_classical_data_test>(n);

    for(int i=0;i<n;i++)
    {
        gendata[i] = generate_single_test();
    }

    return gendata;
}

std::vector<sp_classical_data_validation> DataGenerator::generate_validation(int n)
{
    auto gendata = std::vector<sp_classical_data_validation>(n);

    for(int i=0;i<n;i++)
    {
        gendata[i] = generate_single_validation();
    }

    return gendata;
}

sp_classical_data_test DataGenerator::generate_single_test(int seed)
{
    auto x = generate_single_x(seed);
    auto f_x = compute(x);

    return std::make_shared<ClassicalTestData>(x, f_x);
}

sp_classical_data_validation DataGenerator::generate_single_validation(int seed)
{
    auto x = generate_single_x(seed);
    auto f_x = compute(x);

    return std::make_shared<ClassicalValidationData>(x, f_x);
}