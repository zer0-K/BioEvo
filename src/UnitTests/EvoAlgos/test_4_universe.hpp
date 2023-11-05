//-------------------- EVOLUTIONARY ALGOS - UNIVERSE

#pragma once

#include "test_4_1.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_universe()
    {
        bool is_passed = true;

        std::cout << "Evo algos - universe :" << std::endl;

        is_passed &= launch_tests_evo_algos_universe_flows();

        std::cout << "Evo algos - universe : ";
        passed_print(is_passed);

        return is_passed;
    }
    
}