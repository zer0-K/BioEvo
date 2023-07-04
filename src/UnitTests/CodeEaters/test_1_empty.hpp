#pragma once

#include "test_1_1.hpp"
#include "test_1_2.hpp"


namespace ut_ce
{

    bool launch_tests_code_eaters_empty()
    {
        bool is_passed = true;

        std::cout << "\tEmpty :" << std::endl;

        is_passed &= launch_test_code_eaters_void();
        is_passed &= launch_test_code_eaters_types();

        std::cout << "\tEmpty : ";
        passed_print(is_passed, 1);

        return is_passed;
    }
    
}