// -------------------- OPERATIONS - BOOLEANS - BASIC

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "test_2_1_1_1.hpp"
#include "test_2_1_1_2.hpp"
#include "test_2_1_1_3.hpp"
#include "test_2_1_1_4.hpp"

namespace ut_ce
{
    /**
     * @brief Test simple boolean operations with code eaters
    */
    bool launch_test_code_eaters_operations_boolean_basic()
    {
        bool is_passed = true;

        std::cout << "Code eaters - operations - boolean - basic : " << std::endl;

        is_passed &= launch_test_code_eaters_operations_boolean_basic_id();
        is_passed &= launch_test_code_eaters_operations_boolean_basic_and();
        is_passed &= launch_test_code_eaters_operations_boolean_basic_or();
        is_passed &= launch_test_code_eaters_operations_boolean_basic_xor();

        std::cout << "Code eaters - operations - boolean - basic : ";
        passed_print(is_passed);

        return is_passed;
    }
}