#pragma once

#include "test_1_empty.hpp"
#include "test_2_operations.hpp"

void launch_tests_code_eaters()
{
    bool is_passed = true;

    std::cout << "Unit tests code eaters : " << std::endl;

    is_passed &= launch_tests_code_eaters_empty();
    is_passed &= launch_tests_code_eaters_operations();

    std::cout << "Unit tests code eaters : ";
    passed_print(is_passed, 0);
}