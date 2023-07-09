// -------------------- OPERATIONS - ASSEMBLY

#pragma once

#include "test_2_3_1.hpp"

namespace ut_ce 
{
    bool launch_tests_code_eaters_operations_assembly()
    {
        bool is_passed = true;

        std::cout << "Code eaters - operations - assembly : " << std::endl;

        //is_passed &= launch_test_code_eaters_operations_assembly_typefree();

        std::cout << "Code eaters - operations - assembly : ";
        passed_print(is_passed);

        return is_passed;
    }
}