#pragma once

#include "test_1_empty.hpp"
#include "test_2_phenotypic_body.hpp"

namespace ut_ca
{

    bool launch_tests_classical_algos()
    {
        bool is_passed = true;

        std::cout << std::endl << "******************** CLASSICAL ALGOS ********************" << std::endl << std::endl;

        std::cout << "Unit test classical algorithms : " << std::endl << std::endl;

        is_passed &= launch_tests_classical_algos_empty();
        is_passed &= launch_tests_classical_algos_phenotypic_body();

        std::cout << std::endl << "Unit test classical algorithms : ";
        passed_print(is_passed);

        return is_passed;
    } 

}