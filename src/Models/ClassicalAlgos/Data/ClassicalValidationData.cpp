#include "ClassicalValidationData.hpp"

#include "../../../Utils/Constants.hpp"

void ClassicalValidationData::init()
{
    ClassicalData::init();

    type = CA_DATA_VALIDATION;
    add_type(CA_DATA_VALIDATION);
}

void ClassicalValidationData::set_f_x_predict(double f_x_predict)
{
    this->f_x_predict = f_x_predict;
}

double ClassicalValidationData::get_f_x_predict()
{
    return f_x_predict;
}

double ClassicalValidationData::get_error_abs()
{
    if(f_x>f_x_predict)
        return f_x-f_x_predict;
    return f_x_predict-f_x;
}
