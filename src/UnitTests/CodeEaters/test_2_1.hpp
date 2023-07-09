// -------------------- OPERATIONS - BOOLEANS

#pragma once

#include "test_2_1_1.hpp"

namespace ut_ce 
{
    bool launch_tests_code_eaters_operations_booleans()
    {
        bool is_passed = true;

        std::cout << "Code eaters - operations - booleans : " << std::endl;

        is_passed &= launch_test_code_eaters_operations_booleans_basic();

        std::cout << "Code eaters - operations - booleans : ";
        passed_print(is_passed);

        return is_passed;
    }
}