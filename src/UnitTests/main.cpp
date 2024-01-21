#include "BioEvo/bio_evo.hpp"
#include "ClassicalAlgos/classical_algos.hpp"
#include "ClassicalInfo/classical_info.hpp"
#include "CodeEaters/code_eaters.hpp"
#include "Economy/economy.hpp"
#include "EvoAlgos/evo_algos.hpp"
#include "Finance/finance.hpp"
#include "Maths/maths.hpp"
#include "TheoreticalInfo/theoretical_info.hpp"

int main(int argc, char* argv[])
{
    bool is_passed = true;

    is_passed &= launch_tests_bio_evo();
    is_passed &= ut_ca::launch_tests_classical_algos();
    is_passed &= launch_tests_classical_info();
    is_passed &= ut_ce::launch_tests_code_eaters();
    is_passed &= launch_tests_economy();
    is_passed &= ut_ea::launch_tests_evo_algos();
    is_passed &= launch_tests_finance();
    is_passed &= launch_tests_maths();
    is_passed &= launch_tests_th_info();

    std::cout << std::endl << "All unit tests : ";
    passed_print(is_passed);

    return 0;
}