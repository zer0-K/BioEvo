//-------------------- EVOLUTIONARY ALGOS - X86 ALGO - MOVE

#pragma once

#include "test_2_1_1.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_x86_basic()
    {
        bool is_passed = true;

        std::cout << "Evo algos - x86 - basic :" << std::endl;

        is_passed &= launch_tests_evo_algos_x86_basic_move(); 

        std::cout << "Evo algos - x86 - basic : ";
        passed_print(is_passed);

        return is_passed;
    }

}