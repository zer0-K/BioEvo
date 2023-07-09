#include "test_1_empty.hpp"

void launch_tests_evo_algos()
{
    bool is_passed = true;

    std::cout << "Unit test evolutionary algorithms : " << std::endl;

    is_passed &= launch_test_evo_algos_empty();

    std::cout << "Unit test evolutionary algorithms : ";
    passed_print(is_passed);
}