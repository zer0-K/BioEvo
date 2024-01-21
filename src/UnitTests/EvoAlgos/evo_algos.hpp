#include "test_1_empty.hpp"
#include "test_2_x86.hpp"
#include "test_3_evox.hpp"
#include "test_4_universe.hpp"

namespace ut_ea
{
    bool launch_tests_evo_algos()
    {
        bool is_passed = true;

        std::cout << std::endl << "******************** EVO ALGOS ********************" << std::endl << std::endl;

        std::cout << "Unit test evolutionary algorithms : " << std::endl << std::endl;

        is_passed &= launch_tests_evo_algos_empty();
        is_passed &= launch_tests_evo_algos_x86();
        is_passed &= launch_tests_evo_algos_evox();
        is_passed &= launch_tests_evo_algos_universe();

        std::cout << std::endl << "Unit test evolutionary algorithms : ";
        passed_print(is_passed);

        return is_passed;
    }
}