#include "test_1_empty.hpp"

void launch_tests_th_info()
{
    bool is_passed = true;

    is_passed = is_passed && launch_test_th_info_empty();

    std::cout << "Unit test theoretical computer science : ";
    if(is_passed)
        std::cout << greencol << "passed" << defcol;
    else
        std::cout << redcol << "not passed" << defcol;
    std::cout << std::endl;
}