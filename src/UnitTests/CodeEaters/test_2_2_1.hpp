// -------------------- CODE EATERS - OPERATIONS - INT - BASIC

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "test_2_2_1_1.hpp"
#include "test_2_2_1_2.hpp"
#include "test_2_2_1_3.hpp"

namespace ut_ce
{
    /**
     * @brief Test simple int operations with code eaters
    */
    bool launch_test_code_eaters_operations_int_basic()
    {
        bool is_passed = true;

        std::cout << "Code eaters - operations - int - basic : " << std::endl;

        is_passed &= launch_test_code_eaters_operations_ints_basic_unary();
        is_passed &= launch_test_code_eaters_operations_ints_basic_add();
        is_passed &= launch_test_code_eaters_operations_ints_basic_mult();

        std::cout << "Code eaters - operations - int - basic : ";
        passed_print(is_passed);

        return is_passed;
    }
}