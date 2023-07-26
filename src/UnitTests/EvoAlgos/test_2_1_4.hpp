//-------------------- EVOLUTIONARY ALGOS - X86 ALGO - BASIC - OTHER

#pragma once

#include <iostream>
#include <memory>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"

#include "../../Models/EvoAlgos/X86Algo/X86Algo.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_x86_basic_other()
    {
        bool launch_test_evo_algos_x86_basic_XXX(void);
        bool launch_test_evo_algos_x86_basic_HALT(void);

        bool is_passed = true;

        std::cout << "Evo algos - x86 - basic - other :" << std::endl;

        is_passed &= launch_test_evo_algos_x86_basic_XXX(); 
        is_passed &= launch_test_evo_algos_x86_basic_HALT(); 

        std::cout << "Evo algos - x86 - basic - other : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * does nothing 
    */
    bool launch_test_evo_algos_x86_basic_XXX()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,3>> code {
            { instruction::XXX, 0, 0},
            { instruction::XXX, 0, 1},
            { instruction::XXX, 1, 0},
            { instruction::XXX, 123456789, -123456789}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            1, 2, 3, 4, 5
        };
        algo->set_input_size(input.size());
        algo->set_input(input);

        // output
        algo->set_output_size(3);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if(res[0] != 0 || res[1] != 0 || res[2] != 0)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - other - xxx : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * halt program
    */
    bool launch_test_evo_algos_x86_basic_HALT()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,3>> code {
            { instruction::CPYIN, 0, 0},
            { instruction::HALT, -123456789, 123456789},
            // first input shouldn't be copied to first output
            { instruction::CPYOUT, 0, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            12
        };
        algo->set_input_size(input.size());
        algo->set_input(input);

        // output
        algo->set_output_size(2);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if(res[0] != 0 || res[1] != 0)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - other - halt : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

}