// -------------------- CLASSICAL ALGOS - GENES

#pragma once

#include "test_2_1.hpp"

namespace ut_ca 
{
    bool launch_tests_classical_algos_phenotypic_body()
    {

        bool is_passed = true;

        std::cout << "Classical algos - phenotypic body : " << std::endl;

        is_passed &= launch_tests_classical_algos_phenotypic_body_single();

        std::cout << "Classical algos - phenotypic body : ";
        passed_print(is_passed);

        return is_passed;
    }
}