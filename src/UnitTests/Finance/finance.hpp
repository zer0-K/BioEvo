#include "test_1_empty.hpp"

void launch_tests_finance()
{
    bool is_passed = true;

    is_passed = is_passed && launch_test_finance_empty();

    std::cout << "Unit test finance : ";
    if(is_passed)
        std::cout << greencol << "passed" << defcol;
    else
        std::cout << redcol << "not passed" << defcol;
    std::cout << std::endl;
}