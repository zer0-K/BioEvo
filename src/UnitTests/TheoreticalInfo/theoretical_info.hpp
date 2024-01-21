#include "test_1_empty.hpp"

bool launch_tests_th_info()
{
    bool is_passed = true;

    std::cout << std::endl << "******************** TH INFO ********************" << std::endl << std::endl;

    std::cout << "Unit test theoretical computer science : " << std::endl << std::endl;

    is_passed &= launch_test_th_info_empty();

    std::cout << std::endl << "Unit test theoretical computer science : ";
    passed_print(is_passed);

    return is_passed;
}