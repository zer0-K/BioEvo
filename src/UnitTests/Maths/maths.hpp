#include "test_1_empty.hpp"

void launch_tests_maths()
{
    bool is_passed = true;

    std::cout << "Unit test maths : " << std::endl;

    is_passed &= launch_test_maths_empty();

    std::cout << "Unit test maths : ";
    passed_print(is_passed, 0);
}