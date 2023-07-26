#include "test_1_empty.hpp"

void launch_tests_finance()
{
    bool is_passed = true;

    std::cout << std::endl << "******************** FINANCE ********************" << std::endl << std::endl;

    std::cout << "Unit test finance : " << std::endl << std::endl;

    is_passed &= launch_test_finance_empty();

    std::cout << std::endl << "Unit test finance : ";
    passed_print(is_passed);
}