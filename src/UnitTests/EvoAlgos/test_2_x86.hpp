//-------------------- EVOLUTIONARY ALGOS - X86 ALGO

#pragma once

#include "test_2_1.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_x86()
    {
        bool is_passed = true;

        std::cout << "Evo algos - x86 :" << std::endl;

        is_passed &= launch_tests_evo_algos_x86_basic();

        std::cout << "Evo algos - x86 : ";
        passed_print(is_passed);

        return is_passed;
    }
    
}