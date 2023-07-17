// -------------------- CLASSICAL ALGOS - GENES

#pragma once

#include "test_2_1.hpp"

namespace ut_ca 
{
    bool launch_tests_classical_algos_genes()
    {

        bool is_passed = true;

        std::cout << "Classical algos - genes : " << std::endl;

        is_passed &= launch_tests_classical_algos_genes_single();

        std::cout << "Classical algos - genes : ";
        passed_print(is_passed);

        return is_passed;
    }
}