// -------------------- OPERATIONS - ASSEMBLY

#pragma once

#include "test_2_2_1.hpp"

namespace ut_ce 
{
    bool launch_tests_code_eaters_operations_ints()
    {
        bool is_passed = true;

        std::cout << "Code eaters - operations - int : " << std::endl;

        is_passed &= launch_test_code_eaters_operations_ints_basic();

        std::cout << "Code eaters - operations - int : ";
        passed_print(is_passed);

        return is_passed;
    }
}