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
    launch_tests_bio_evo();
    launch_tests_classical_algos();
    launch_tests_classical_info();
    launch_tests_code_eaters();
    launch_tests_economy();
    launch_tests_evo_algos();
    launch_tests_finance();
    launch_tests_maths();
    launch_tests_th_info();

    return 0;
}