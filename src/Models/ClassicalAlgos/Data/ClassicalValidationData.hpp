#pragma once

#include "ClassicalData.hpp"

class ClassicalValidationData : public ClassicalData
{
protected:
    /**
     * @brief estimation of f_x
    */
    double f_x_predict;

public:
    using ClassicalData::ClassicalData;

    void init() override;

    void set_f_x_predict(double f_x_predict);

    double get_f_x_predict();
    double get_error_abs();
};

typedef std::shared_ptr<ClassicalValidationData> sp_classical_data_validation;