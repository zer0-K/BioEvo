//-------------------- EVOLUTIONARY ALGOS - X86 ALGO - BASIC - JUMPS

#pragma once

#include <iostream>
#include <memory>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"

#include "../../Models/EvoAlgos/X86Algo/X86Algo.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_x86_basic_jumps()
    {
        bool launch_test_evo_algos_x86_basic_CMP(void);
        bool launch_test_evo_algos_x86_basic_JMP(void);
        bool launch_test_evo_algos_x86_basic_JRA(void);
        bool launch_test_evo_algos_x86_basic_JRS(void);
        bool launch_test_evo_algos_x86_basic_JE(void);
        bool launch_test_evo_algos_x86_basic_JL(void);
        bool launch_test_evo_algos_x86_basic_JG(void);

        bool is_passed = true;

        std::cout << "Evo algos - x86 - basic - jumps :" << std::endl;

        is_passed &= launch_test_evo_algos_x86_basic_CMP(); 
        is_passed &= launch_test_evo_algos_x86_basic_JMP(); 
        is_passed &= launch_test_evo_algos_x86_basic_JRA(); 
        is_passed &= launch_test_evo_algos_x86_basic_JRS(); 
        is_passed &= launch_test_evo_algos_x86_basic_JE(); 
        is_passed &= launch_test_evo_algos_x86_basic_JL(); 
        is_passed &= launch_test_evo_algos_x86_basic_JG(); 

        std::cout << "Evo algos - x86 - basic - jumps : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * comparison : 0 if equal, 1 if arg1<arg2, -1 if > 
    */
    bool launch_test_evo_algos_x86_basic_CMP()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,3>> code {
            { instruction::CPYIN, 0, 0},
            { instruction::CPYIN, 1, 1},
            // compare second input with itself
            { instruction::CPY, 2, 1},
            { instruction::CMP, 2, 2},
            { instruction::CPYOUT, 0, 2},
            // compare second input with first
            { instruction::CPY, 2, 1},
            { instruction::CMP, 2, 0},
            { instruction::CPYOUT, 1, 2},
            // compare first input with second
            { instruction::CPY, 2, 0},
            { instruction::CMP, 2, 1},
            { instruction::CPYOUT, 2, 2}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            3, 6
        };
        algo->set_input_size(input.size());
        algo->set_input(input);

        // output
        algo->set_output_size(3);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if(res[0] != 0 || res[1] != -1 || res[2] != 1)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - cmp : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * absolute jump
    */
    bool launch_test_evo_algos_x86_basic_JMP()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,3>> code {
            // copy args
            { instruction::CPYIN, 0, 0},
            { instruction::CPYIN, 1, 1},
            { instruction::CPYIN, 2, 2},
            // jump to code at line given in third arg
            { instruction::JMP, 3, 2},
            // should be ignored
            { instruction::XXX, 0, 0},
            { instruction::CPYOUT, 0, 0},
            // line 6
            { instruction::CPYOUT, 1, 1}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            100, 667, 6
        };
        algo->set_input_size(input.size());
        algo->set_input(input);

        // output
        algo->set_output_size(2);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if(res[0] != 0 || res[1] != 667)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - jmp : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * relative positive jump
    */
    bool launch_test_evo_algos_x86_basic_JRA()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,3>> code {
            // copy args
            { instruction::CPYIN, 0, 0},
            { instruction::CPYIN, 1, 1},
            { instruction::CPYIN, 2, 2},
            // jump to code at line given in third arg
            { instruction::JRA, 3, 2},
            // should be ignored
            { instruction::XXX, 0, 0},
            { instruction::CPYOUT, 0, 0},
            // line 6
            { instruction::CPYOUT, 1, 1}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            100, 667, 3
        };
        algo->set_input_size(input.size());
        algo->set_input(input);

        // output
        algo->set_output_size(2);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if(res[0] != 0 || res[1] != 667)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - jra : ";
            passed_print(is_passed);
        }

        return is_passed;
    }


    /**
     * relative negative jump
    */
    bool launch_test_evo_algos_x86_basic_JRS()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,3>> code {
            // copy args
            { instruction::CPYIN, 0, 0},
            { instruction::CPYIN, 1, 1},
            { instruction::CPYIN, 2, 2},
            // jump to code at line given in third arg
            { instruction::JRS, 3, 2},
            // should be ignored
            { instruction::XXX, 0, 0},
            { instruction::CPYOUT, 0, 0},
            // line 6
            { instruction::CPYOUT, 1, 1}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            100, 667, -3
        };
        algo->set_input_size(input.size());
        algo->set_input(input);

        // output
        algo->set_output_size(2);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if(res[0] != 0 || res[1] != 667)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - jrs : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * conditional jump : equality (O)
    */
    bool launch_test_evo_algos_x86_basic_JE()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,3>> code {
            // copy args
            { instruction::CPYIN, 0, 0},
            { instruction::CPYIN, 1, 1},
            { instruction::CPYIN, 2, 2},
            { instruction::CPYIN, 3, 1},
            { instruction::CMP, 3, 0},
            // jump to code at line given in third arg if arg0==arg1
            { instruction::JE, 2, 3},
            // should be ignored
            { instruction::XXX, 0, 0},
            { instruction::CPYOUT, 2, 0},
            // line 6
            { instruction::CPYOUT, 1, 1}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            100, 100, 6
        };
        algo->set_input_size(input.size());
        algo->set_input(input);

        // output
        algo->set_output_size(2);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if(res[0] != 0 || res[1] != 100)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - je : ";
            passed_print(is_passed);
        }

        return is_passed;
    }


    /**
     * conditional jump : negative
    */
    bool launch_test_evo_algos_x86_basic_JL()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,3>> code {
            // copy args
            { instruction::CPYIN, 0, 0},
            { instruction::CPYIN, 1, 1},
            { instruction::CPYIN, 2, 2},
            { instruction::CPYIN, 3, 1},
            { instruction::CMP, 3, 0},
            // jump to code at line given in third arg if arg0>arg1
            { instruction::JL, 2, 3},
            // should be ignored
            { instruction::XXX, 0, 0},
            { instruction::CPYOUT, 2, 0},
            // line 6
            { instruction::CPYOUT, 1, 1}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            100, 99, 6
        };
        algo->set_input_size(input.size());
        algo->set_input(input);

        // output
        algo->set_output_size(2);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if(res[0] != 0 || res[1] != 99)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - jl : ";
            passed_print(is_passed);
        }

        return is_passed;
    }


    /**
     * conditional jump : positive
    */
    bool launch_test_evo_algos_x86_basic_JG()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,3>> code {
            // copy args
            { instruction::CPYIN, 0, 0},
            { instruction::CPYIN, 1, 1},
            { instruction::CPYIN, 2, 2},
            { instruction::CPYIN, 3, 1},
            { instruction::CMP, 3, 0},
            // jump to code at line given in third arg if arg0<arg1
            { instruction::JG, 2, 3},
            // should be ignored
            { instruction::XXX, 0, 0},
            { instruction::CPYOUT, 2, 0},
            // line 6
            { instruction::CPYOUT, 1, 1}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            100, 101, 6
        };
        algo->set_input_size(input.size());
        algo->set_input(input);

        // output
        algo->set_output_size(2);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if(res[0] != 0 || res[1] != 101)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - jg : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

}