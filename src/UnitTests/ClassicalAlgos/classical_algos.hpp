#pragma once

#include "test_1_empty.hpp"
#include "test_2_genes.hpp"

namespace ut_ca
{

    void launch_tests_classical_algos()
    {
        bool is_passed = true;

        std::cout << "Unit test classical algorithms : " << std::endl;

        is_passed &= launch_tests_classical_algos_empty();
        is_passed &= launch_tests_classical_algos_genes();

        std::cout << "Unit test classical algorithms : ";
        passed_print(is_passed);
    } 

}