#pragma once

#include "test_2_1.hpp"
#include "test_2_2.hpp"

namespace ut_ce
{
    bool launch_tests_code_eaters_operations()
    {
        bool is_passed = true;

        std::cout << "Code eaters - operations : " << std::endl;

        is_passed &= launch_tests_code_eaters_operations_booleans();
        is_passed &= launch_tests_code_eaters_operations_ints();

        std::cout << "Code eaters - operations : ";
        passed_print(is_passed);

        return is_passed;
    }
}