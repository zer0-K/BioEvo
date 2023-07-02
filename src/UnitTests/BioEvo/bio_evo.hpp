#include "test_1_empty.hpp"

void launch_tests_bio_evo()
{
    bool is_passed = true;

    std::cout << "Unit test evolutionary biology : " << std::endl;

    is_passed &= launch_test_bio_evo_empty();

    std::cout << "Unit test evolutionary biology : ";
    passed_print(is_passed, 0);
}