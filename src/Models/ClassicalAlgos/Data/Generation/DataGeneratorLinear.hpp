#pragma once

#include "DataGenerator.hpp"

#include <vector>

class DataGeneratorLinear : public DataGenerator
{
protected:
    std::vector<double> coeffs;

public:
    DataGeneratorLinear();
    //using DataGenerator::DataGenerator;

    /// @see DataGenerator::init_default
    void init_default() override;

    /// @see DataGenerator::init_custom
    void init_custom() override;

    /// @see DataGenerator::generate_single_x 
    std::vector<double> generate_single_x(int seed = -1);

    /// @see DataGenerator::compute 
    double compute(std::vector<double> x) override;

    /// @brief print model on console
    void print_model();
};

typedef std::shared_ptr<DataGeneratorLinear> sp_datagen_linear;