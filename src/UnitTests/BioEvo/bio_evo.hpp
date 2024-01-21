#include "test_1_empty.hpp"

bool launch_tests_bio_evo()
{
    bool is_passed = true;

    std::cout << std::endl << "******************** BIOEVO ********************" << std::endl << std::endl;

    std::cout << "Unit test evolutionary biology : " << std::endl << std::endl;

    is_passed &= launch_test_bio_evo_empty();

    std::cout << std::endl << "Unit test evolutionary biology : ";
    passed_print(is_passed);

        return is_passed;
}