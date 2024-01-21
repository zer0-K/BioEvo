#include "test_1_empty.hpp"

bool launch_tests_classical_info()
{
    bool is_passed = true;

    std::cout << std::endl << "******************** CLASSICAL INFO ********************" << std::endl << std::endl;

    std::cout << "Unit test classical info : " << std::endl << std::endl;

   is_passed = is_passed && launch_test_classical_info_empty();

    std::cout << std::endl << "Unit test classical info : ";
    passed_print(is_passed);

    return is_passed;
}