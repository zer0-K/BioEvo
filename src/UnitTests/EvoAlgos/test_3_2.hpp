//-------------------- EVOLUTIONARY ALGOS - EVO X - non evolved programs

#pragma once

#include "test_3_2_1.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_evox_evolution1()
    {
        bool is_passed = true;

        std::cout << "Evo algos - evox - evolution 1 :" << std::endl;

        is_passed &= launch_tests_evo_algos_evox_evolution1_replication();

        std::cout << "Evo algos - evox - evolution 1 : ";
        passed_print(is_passed);

        return is_passed;
    }
    
}