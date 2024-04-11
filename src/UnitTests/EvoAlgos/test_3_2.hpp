//-------------------- EVOLUTIONARY ALGOS - EVO X - non evolved programs

#pragma once

#include "test_3_2_1.hpp"
#include "test_3_2_2.hpp"
#include "test_3_2_3.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_evox_evolution_preliminaries()
    {
        bool is_passed = true;

        std::cout << "Evo algos - evox - evolution preliminaries :" << std::endl;

        is_passed &= launch_tests_evo_algos_evox_evolution_preliminaries_behavior_simple();
        is_passed &= launch_tests_evo_algos_evox_evolution_preliminaries_autopoiesis();
        is_passed &= launch_tests_evo_algos_evox_evolution_preliminaries_synthesis();

        std::cout << "Evo algos - evox - evolution preliminaries: ";
        passed_print(is_passed);

        return is_passed;
    }
    
}