#include "ClassicalTestData.hpp"

#include "../../../Utils/Constants.hpp"

void ClassicalTestData::init()
{
    ClassicalData::init();

    type = CA_DATA_TEST;
    add_type(CA_DATA_TEST);
}

double ClassicalTestData::get_f_x()
{
    return f_x;
}