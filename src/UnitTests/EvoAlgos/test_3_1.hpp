//-------------------- EVOLUTIONARY ALGOS - EVO X - GENES

#pragma once

#include "test_3_1_1.hpp"
#include "test_3_1_2.hpp"
#include "test_3_1_3.hpp"
#include "test_3_1_4.hpp"
#include "test_3_1_5.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_evox_genes()
    {
        bool is_passed = true;

        std::cout << "Evo algos - evox - genes :" << std::endl;

        is_passed &= launch_tests_evo_algos_evox_genes_basic();
        is_passed &= launch_tests_evo_algos_evox_genes_mutations();
        //is_passed &= launch_tests_evo_algos_evox_genes_markers();
        is_passed &= launch_tests_evo_algos_evox_genes_exec();
        is_passed &= launch_tests_evo_algos_evox_genes_regen();

        std::cout << "Evo algos - evox - genes : ";
        passed_print(is_passed);

        return is_passed;
    }
    
}