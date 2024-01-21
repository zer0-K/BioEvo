#include "test_1_empty.hpp"

bool launch_tests_economy()
{
    bool is_passed = true;

    std::cout << std::endl << "******************** ECONOMY ********************" << std::endl << std::endl;

    std::cout << "Unit test economy : " << std::endl << std::endl;

    is_passed &= launch_test_economy_empty();

    std::cout << std::endl << "Unit test economy : ";
    passed_print(is_passed);

    return is_passed;
}