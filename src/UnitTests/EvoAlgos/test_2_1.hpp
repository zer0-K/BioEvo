//-------------------- EVOLUTIONARY ALGOS - X86 ALGO - basic

#pragma once

#include "test_2_1_1.hpp"
#include "test_2_1_2.hpp"
#include "test_2_1_3.hpp"
#include "test_2_1_4.hpp"
#include "test_2_1_5.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_x86_basic()
    {
        bool is_passed = true;

        std::cout << "Evo algos - x86 - basic :" << std::endl;

        is_passed &= launch_tests_evo_algos_x86_basic_move(); 
        is_passed &= launch_tests_evo_algos_x86_basic_maths(); 
        is_passed &= launch_tests_evo_algos_x86_basic_jumps(); 
        is_passed &= launch_tests_evo_algos_x86_basic_other(); 
        is_passed &= launch_tests_evo_algos_x86_basic_random(); 

        std::cout << "Evo algos - x86 - basic : ";
        passed_print(is_passed);

        return is_passed;
    }

}