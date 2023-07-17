#pragma once

#include "ClassicalData.hpp"

class ClassicalTestData : public ClassicalData
{
public:
    using ClassicalData::ClassicalData;

    void init() override;

    double get_f_x();
};

typedef std::shared_ptr<ClassicalTestData> sp_classical_data_test;