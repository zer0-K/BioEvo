//-------------------- EVOLUTIONARY ALGOS - X86 ALGO - BASIC - RANDOM

#pragma once

#include <iostream>
#include <memory>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"

#include "../../Models/EvoAlgos/X86Algo/X86Algo.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_x86_basic_random()
    {
        bool launch_test_evo_algos_x86_basic_random_normal(void);
        bool launch_test_evo_algos_x86_basic_random_unif(void);

        bool is_passed = true;

        std::cout << "Evo algos - x86 - basic - random :" << std::endl;

        //is_passed &= launch_test_evo_algos_x86_basic_random_normal(); 
        is_passed &= launch_test_evo_algos_x86_basic_random_unif(); 

        std::cout << "Evo algos - x86 - basic - random : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief normal law 
     * TODO : for the moment X86 Algo only has ints
    */
    bool launch_test_evo_algos_x86_basic_random_normal()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,3>> code {
            { instruction::CPYIN, 0, 0},
            { instruction::CPYIN, 1, 1},
            { instruction::CPY, 2, 0},
            { instruction::RN, 4, 4},
            { instruction::ADD, 3, 4},
            { instruction::DEC, 2, 2},
            { instruction::JG, 1, 2},
            { instruction::DIV, 3, 0},
            { instruction::CPYOUT, 0, 3}
        };
        algo->reset_code_to_size(code.size());
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            1000, 3
        };
        algo->set_input_size(input.size());
        algo->set_input(input);

        // output
        algo->set_output_size(1);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if( std::abs(res[0]) > 0.01 )
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - random - normal : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief uniform law
    */
    bool launch_test_evo_algos_x86_basic_random_unif()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,3>> code {
            { instruction::CPYIN, 0, 0},
            { instruction::CPYIN, 1, 1},
            { instruction::CPYIN, 2, 2},
            { instruction::CPYIN, 3, 3},
            { instruction::CPY, 4, 0},
            { instruction::RUISL, 1, 1},
            { instruction::RUISU, 2, 2},
            { instruction::RUI, 6, 6},
            { instruction::ADD, 5, 6},
            { instruction::DEC, 4, 4},
            { instruction::JG, 3, 4},
            { instruction::DIV, 5, 0},
            { instruction::CPYOUT, 0, 5}
        };
        algo->reset_code_to_size(code.size());
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            1000, 11, 16, 7
        };
        algo->set_input_size(input.size());
        algo->set_input(input);

        // output
        algo->set_output_size(1);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        // result is 13.666 but since it's ints...
        if( std::abs(res[0]-13) > 0.01 )
        {
            is_passed = false;
        }

       if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - random - unif : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

}