//-------------------- EVOLUTIONARY ALGOS - X86 ALGO - MOVE

#pragma once

#include <iostream>
#include <memory>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"

#include "../../Models/EvoAlgos/X86Algo/X86Algo.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_x86_basic_move()
    {
        bool launch_test_evo_algos_x86_basic_MOVINOUT(void);

        bool is_passed = true;

        std::cout << "Evo algos - x86 - move :" << std::endl;

        is_passed &= launch_test_evo_algos_x86_basic_MOVINOUT(); 

        std::cout << "Evo algos - x86 - move : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * load input, move to data and move to output
    */
    bool launch_test_evo_algos_x86_basic_MOVINOUT()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,3>> code {
            { instruction::MOVIN, 10, 2},
            { instruction::MOVOUT, 3, 10}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            0, 0, 8, 0, 0
        };
        algo->set_input_size(input.size());
        algo->set_input(input);

        // output
        algo->set_output_size(5);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if(res[0] != 0 || res[1] != 0 || res[2] != 0 || res[3] != 8 || res[4] != 0)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - move - move in/out : ";
            passed_print(is_passed);
        }

        return is_passed;

    }
    
}