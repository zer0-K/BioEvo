#pragma once

#include "test_2_1.hpp"

namespace ut_ce
{
    bool launch_tests_code_eaters_operations()
    {
        bool is_passed = true;

        std::cout << "\tOperations : " << std::endl;

        is_passed &= launch_tests_code_eaters_operations_booleans();

        std::cout << "\tOperations : ";
        passed_print(is_passed, 1);

        return is_passed;
    }
}