#pragma once

#include "test_1_empty.hpp"
#include "test_2_operations.hpp"
#include "test_3_metadata.hpp"

namespace ut_ce 
{

    void launch_tests_code_eaters()
    {
        bool is_passed = true;

        std::cout << "Unit tests code eaters : " << std::endl;

        is_passed &= launch_tests_code_eaters_empty();
        is_passed &= launch_tests_code_eaters_operations();
        is_passed &= launch_tests_code_eaters_metadata();

        std::cout << "Unit tests code eaters : ";
        passed_print(is_passed);
    }

}