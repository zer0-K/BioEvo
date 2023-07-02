// -------------------- OPERATIONS - BOOLEANS

#pragma once

#include "test_2_1_1.hpp"

bool launch_tests_code_eaters_operations_booleans()
{
    bool is_passed = true;

    std::cout << "\t\tBoolean operations : " << std::endl;

    is_passed &= launch_test_code_eaters_operations_booleans_basic();

    std::cout << "\t\tBoolean operations : ";
    passed_print(is_passed, 1);

    return is_passed;
}