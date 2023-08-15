//-------------------- EVOLUTIONARY ALGOS - X86 ALGO - BASIC - MOVE

#pragma once

#include <iostream>
#include <memory>

#include "X86TesterHelper.hpp"
#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"

#include "../../Models/EvoAlgos/X86Algo/X86Algo.hpp"

namespace ut_ea
{
    bool launch_tests_evo_algos_x86_basic_move()
    {
        bool launch_test_evo_algos_x86_basic_CPYINOUT(void);
        bool launch_test_evo_algos_x86_basic_MOV(void);
        bool launch_test_evo_algos_x86_basic_CPY(void);

        bool is_passed = true;

        std::cout << "Evo algos - x86 - basic - move :" << std::endl;

        is_passed &= launch_test_evo_algos_x86_basic_CPYINOUT(); 
        is_passed &= launch_test_evo_algos_x86_basic_MOV(); 
        is_passed &= launch_test_evo_algos_x86_basic_CPY(); 

        std::cout << "Evo algos - x86 - basic - move : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * load input, copy to memory and copy to output
    */
    bool launch_test_evo_algos_x86_basic_CPYINOUT()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            { instruction::CPYIN, 0, 0, 0, 10, 2, 0},
            { instruction::CPYOUT, 0, 0, 0, 3, 10, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            0, 0, 8, 0, 0
        };
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
            std::cout << "Evo algos - x86 - basic - move - copy in/out : ";
            passed_print(is_passed);
        }

        return is_passed;

    }

    /**
     * load input, copy to memory, move and copy to output
    */
    bool launch_test_evo_algos_x86_basic_MOV()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            { instruction::CPYIN, 0, 0, 0, 10, 2, 0},
            { instruction::MOV, 0, 0, 0, 20, 10, 0},
            { instruction::CPYOUT, 0, 0, 0, 3, 20, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            0, 0, 8, 0, 0
        };
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
            std::cout << "Evo algos - x86 - basic - move - move : ";
            passed_print(is_passed);
        }

        return is_passed;

    }

    /**
     * load input, copy to memory, copy in memory and copy to output
    */
    bool launch_test_evo_algos_x86_basic_CPY()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            { instruction::CPYIN, 0, 0, 0, 10, 2, 0},
            { instruction::CPY, 0, 0, 0, 20, 10, 0},
            { instruction::CPYOUT, 0, 0, 0, 3, 10, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            0, 0, 8, 0, 0
        };
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
            std::cout << "Evo algos - x86 - basic - move - copy : ";
            passed_print(is_passed);
        }

        return is_passed;

    }
    
}