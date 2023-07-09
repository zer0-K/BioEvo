#include "test_1_empty.hpp"

void launch_tests_th_info()
{
    bool is_passed = true;

    std::cout << "Unit test theoretical computer science : " << std::endl;

    is_passed &= launch_test_th_info_empty();

    std::cout << "Unit test theoretical computer science : ";
    passed_print(is_passed);
}