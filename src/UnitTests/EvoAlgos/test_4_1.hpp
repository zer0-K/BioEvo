//-------------------- EVOLUTIONARY ALGOS - UNIVERSE - FLOWS

#pragma once

#include "test_4_1_1.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_universe_flows()
    {
        bool is_passed = true;

        std::cout << "Evo algos - universe - flows :" << std::endl;

        is_passed &= launch_tests_evo_algos_universe_flows_basic();

        std::cout << "Evo algos - universe - flows : ";
        passed_print(is_passed);

        return is_passed;
    }
    
}