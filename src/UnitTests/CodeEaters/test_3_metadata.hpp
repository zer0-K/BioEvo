#pragma once

#include "test_3_1.hpp"

namespace ut_ce
{

    bool launch_tests_code_eaters_metadata()
    {
        bool is_passed = true;

        std::cout << "Code eaters - meta : " << std::endl;

        is_passed &= launch_test_code_eaters_metadata_counter();

        std::cout << "Code eaters - meta : ";
        passed_print(is_passed);

        return is_passed;
    }
    
}