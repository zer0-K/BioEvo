#pragma once

#include "test_3_1.hpp"

namespace ut_ce
{

    bool launch_tests_code_eaters_metadata()
    {
        bool is_passed = true;

        std::cout << "\tMetadata : " << std::endl;

        is_passed &= launch_tests_code_eaters_metadata();

        std::cout << "\tMetadata : ";
        passed_print(is_passed, 1);

        return is_passed;
    }
    
}