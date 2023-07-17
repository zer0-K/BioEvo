#pragma once

#include "../ClassicalTestData.hpp"
#include "../ClassicalValidationData.hpp"

class DataGenerator
{
public:
    DataGenerator();

    /**
     * @brief automatic init
    */
    virtual void init_default() {};

    /**
     * @brief custom init
    */
    virtual void init_custom() {};


    /**
     * @brief generate test data
     * 
     * @param[in] n number of data to generate
    */
    std::vector<sp_classical_data_test> generate_test(int n);

    /**
     * @brief generate validation data
     * 
     * @param[in] n number of data to generate
    */
    std::vector<sp_classical_data_validation> generate_validation(int n);

    /**
     * @brief generate a single test data
     * 
     * @param[in] seed seed for data generation (@see generate_single_x)
    */
    sp_classical_data_test generate_single_test(int seed = -1);

    /**
     * @brief generate a single validation data
     * 
     * @param[in] seed seed for data generation (@see generate_single_x)
    */
    sp_classical_data_validation generate_single_validation(int seed = -1);

    /**
     * @brief generate an input
     * 
     * @param[in] seed seed for data generation
     * 
     * If seed is -1, will generate a random x
     * Otherwise, you can create custom input generation with the seed
    */
    virtual std::vector<double> generate_single_x(int seed = -1) = 0;

    /**
     * @brief compute f(x)
     * 
     * @param[in] x input
     * 
     * @return f(x)
    */
    virtual double compute(std::vector<double> x) = 0;
};

typedef std::shared_ptr<DataGenerator> sp_datagen;