#include "test_1_empty.hpp"

void launch_tests_economy()
{
    bool is_passed = true;

    std::cout << "Unit test economy : " << std::endl;

    is_passed &= launch_test_economy_empty();

    std::cout << "Unit test economy : ";
    passed_print(is_passed);
}