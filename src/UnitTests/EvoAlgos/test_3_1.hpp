//-------------------- EVOLUTIONARY ALGOS - EVO X - MOLECULAR BODY

#pragma once

#include "test_3_1_1.hpp"
#include "test_3_1_2.hpp"
#include "test_3_1_3.hpp"
#include "test_3_1_4.hpp"
#include "test_3_1_5.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_evox_molecular_body()
    {
        bool is_passed = true;

        std::cout << "Evo algos - evox - molecular body :" << std::endl;

        is_passed &= launch_tests_evo_algos_evox_molecular_body_basic();
        is_passed &= launch_tests_evo_algos_evox_molecular_body_mutations();
        //is_passed &= launch_tests_evo_algos_evox_molecular_body_markers();
        is_passed &= launch_tests_evo_algos_evox_molecular_body_exec();
        is_passed &= launch_tests_evo_algos_evox_molecular_body_regen();

        std::cout << "Evo algos - evox - molecular body : ";
        passed_print(is_passed);

        return is_passed;
    }
    
}