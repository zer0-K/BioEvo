#include "test_1_empty.hpp"

void launch_tests_evo_algos()
{
    bool is_passed = true;

    is_passed = is_passed && launch_test_evo_algos_empty();

    std::cout << "Unit test evolutionary algorithms : ";
    if(is_passed)
        std::cout << greencol << "passed" << defcol;
    else
        std::cout << redcol << "not passed" << defcol;
    std::cout << std::endl;
}