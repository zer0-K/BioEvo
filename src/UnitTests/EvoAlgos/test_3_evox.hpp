//-------------------- EVOLUTIONARY ALGOS - EVO X

#pragma once

#include "test_3_1.hpp"
#include "test_3_2.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_evox()
    {
        bool is_passed = true;

        std::cout << "Evo algos - evox :" << std::endl;

        is_passed &= launch_tests_evo_algos_evox_molecular_body();
        is_passed &= launch_tests_evo_algos_evox_evolution_preliminaries();

        std::cout << "Evo algos - evox : ";
        passed_print(is_passed);

        return is_passed;
    }
    
}