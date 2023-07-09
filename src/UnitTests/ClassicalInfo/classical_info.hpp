#include "test_1_empty.hpp"

void launch_tests_classical_info()
{
    bool is_passed = true;

    std::cout << "Unit test classical info : ";

    is_passed = is_passed && launch_test_classical_info_empty();

    std::cout << "Unit test classical info : ";
    passed_print(is_passed);
}