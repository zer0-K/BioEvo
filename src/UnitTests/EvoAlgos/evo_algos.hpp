#include "test_1_empty.hpp"
#include "test_2_x86.hpp"

namespace ut_ea
{
    void launch_tests_evo_algos()
    {
        bool is_passed = true;

        std::cout << "Unit test evolutionary algorithms : " << std::endl;

        is_passed &= launch_tests_evo_algos_empty();
        is_passed &= launch_tests_evo_algos_x86();

        std::cout << "Unit test evolutionary algorithms : ";
        passed_print(is_passed);
    }
}