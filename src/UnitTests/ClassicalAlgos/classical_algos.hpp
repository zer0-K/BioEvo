#include "test_1_empty.hpp"

void launch_tests_classical_algos()
{
    bool is_passed = true;

    std::cout << "Unit test classical algorithms : " << std::endl;

    is_passed &= launch_test_classical_algos_empty();

    std::cout << "Unit test classical algorithms : ";
    passed_print(is_passed);
}