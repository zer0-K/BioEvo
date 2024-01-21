#include "test_1_empty.hpp"

bool launch_tests_maths()
{
    bool is_passed = true;

    std::cout << std::endl << "******************** MATHS ********************" << std::endl << std::endl;

    std::cout << "Unit test maths : " << std::endl << std::endl;

    is_passed &= launch_test_maths_empty();

    std::cout << std::endl << "Unit test maths : ";
    passed_print(is_passed);

    return is_passed;
}