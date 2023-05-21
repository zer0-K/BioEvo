#pragma once

#include <vector>

#include "QuantumData.hpp"

class TestData: public QuantumData<std::vector<double>, double>
{
public:
    /**
     * @brief @see QuantumData constructor
    */
    TestData(std::vector<double> x, double f_x);
};

typedef std::shared_ptr<TestData> sp_testdata;