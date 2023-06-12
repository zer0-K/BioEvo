#include "test_1_empty.hpp"

void launch_tests_code_eaters()
{
    bool is_passed = true;

    is_passed = is_passed && launch_test_code_eaters_empty();

    std::cout << "Unit test code eaters : ";
    if(is_passed)
        std::cout << greencol << "passed" << defcol;
    else
        std::cout << redcol << "not passed" << defcol;
    std::cout << std::endl;
}