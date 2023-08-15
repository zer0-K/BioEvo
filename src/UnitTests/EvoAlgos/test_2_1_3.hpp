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
        bool launch_test_evo_algos_x86_basic_JLE(void);
        bool launch_test_evo_algos_x86_basic_JGE(void);
        bool launch_test_evo_algos_x86_basic_JRE(void);
        bool launch_test_evo_algos_x86_basic_JRL(void);
        bool launch_test_evo_algos_x86_basic_JRG(void);
        bool launch_test_evo_algos_x86_basic_JRLE(void);
        bool launch_test_evo_algos_x86_basic_JRGE(void);

        bool is_passed = true;

        std::cout << "Evo algos - x86 - basic - jumps :" << std::endl;

        is_passed &= launch_test_evo_algos_x86_basic_CMP(); 
        is_passed &= launch_test_evo_algos_x86_basic_JMP(); 
        is_passed &= launch_test_evo_algos_x86_basic_JRA(); 
        is_passed &= launch_test_evo_algos_x86_basic_JRS(); 
        is_passed &= launch_test_evo_algos_x86_basic_JE(); 
        is_passed &= launch_test_evo_algos_x86_basic_JL(); 
        is_passed &= launch_test_evo_algos_x86_basic_JG(); 
        is_passed &= launch_test_evo_algos_x86_basic_JLE(); 
        is_passed &= launch_test_evo_algos_x86_basic_JGE(); 
        is_passed &= launch_test_evo_algos_x86_basic_JRE(); 
        is_passed &= launch_test_evo_algos_x86_basic_JRL(); 
        is_passed &= launch_test_evo_algos_x86_basic_JRG(); 
        is_passed &= launch_test_evo_algos_x86_basic_JRLE(); 
        is_passed &= launch_test_evo_algos_x86_basic_JRGE(); 

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
        std::vector<std::array<int,SIZE_INSTR>> code {
            { instruction::CPYIN, 0, 0, 0, 0, 0, 0},
            { instruction::CPYIN, 0, 0, 0, 1, 1, 0},
            // compare first input with itself
            { instruction::CMP, 0, 0, 0, 2, 1, 1},
            { instruction::CPYOUT, 0, 0, 0, 0, 2, 0},
            // compare second input with first
            { instruction::CMP, 0, 0, 0, 2, 1, 0},
            { instruction::CPYOUT, 0, 0, 0, 1, 2, 0},
            // compare first input with second
            { instruction::CMP, 0, 0, 0, 2, 0, 1},
            { instruction::CPYOUT, 0, 0, 0, 2, 2, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            3, 6
        };
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
        std::vector<std::array<int,SIZE_INSTR>> code {
            // copy args
            { instruction::CPYIN, 0, 0, 0, 0, 0, 0},
            { instruction::CPYIN, 0, 0, 0, 1, 1, 0},
            { instruction::CPYIN, 0, 0, 0, 2, 2, 0},
            // jump to code at line given in third arg
            { instruction::JMP, 0, 0, 0, 2, 0, 0},
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::CPYOUT, 0, 0, 0, 0, 0, 0},
            // line 6
            { instruction::CPYOUT, 0, 0, 0, 1, 1, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            100, 667, 6
        };
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
        std::vector<std::array<int,SIZE_INSTR>> code {
            // copy args
            { instruction::CPYIN, 0, 0, 0, 0, 0, 0},
            { instruction::CPYIN, 0, 0, 0, 1, 1, 0},
            { instruction::CPYIN, 0, 0, 0, 2, 2, 0},
            // jump to code at line given in third arg
            { instruction::JRA, 0, 0, 0, 2, 0, 0},
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::CPYOUT, 0, 0, 0, 0, 0, 0},
            // line 6
            { instruction::CPYOUT, 0, 0, 0, 1, 1, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            100, 667, 3
        };
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
        std::vector<std::array<int,SIZE_INSTR>> code {
            // copy args
            { instruction::CPYIN, 0, 0, 0, 0, 0, 0},
            { instruction::CPYIN, 0, 0, 0, 1, 1, 0},
            { instruction::CPYIN, 0, 0, 0, 2, 2, 0},
            // jump to code at line given in third arg
            { instruction::JRS, 0, 0, 0, 2, 0, 0},
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::CPYOUT, 0, 0, 0, 0, 0, 0},
            // line 6
            { instruction::CPYOUT, 0, 0, 0, 1, 1, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            100, 667, -3
        };
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
        std::vector<std::array<int,SIZE_INSTR>> code {
            // copy args
            { instruction::CPYIN, 0, 0, 0, 0, 0, 0},
            { instruction::CPYIN, 0, 0, 0, 1, 1, 0},
            { instruction::CPYIN, 0, 0, 0, 2, 2, 0},
            // jump to code at line given in third arg if arg0==arg1
            { instruction::JE, 0, 0, 0, 2, 1, 0},
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::CPYOUT, 0, 0, 0, 0, 0, 0},
            // line 6
            { instruction::CPYOUT, 0, 0, 0, 1, 2, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            100, 100, 6
        };
        algo->set_input(input);

        // output
        algo->set_output_size(2);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if(res[0] != 0 || res[1] != 6)
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
     * jump if lower
    */
    bool launch_test_evo_algos_x86_basic_JL()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            // copy args
            { instruction::CPYIN, 0, 0, 0, 0, 0, 0},
            { instruction::CPYIN, 0, 0, 0, 1, 1, 0},
            { instruction::CPYIN, 0, 0, 0, 2, 2, 0},
            // jump to code at line given in third arg if arg0>arg1
            { instruction::JL, 0, 0, 0, 2, 1, 0},
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::CPYOUT, 0, 0, 0, 0, 0, 0},
            // line 6
            { instruction::CPYOUT, 0, 0, 0, 1, 1, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            100, 99, 6
        };
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
     * jump if greater
    */
    bool launch_test_evo_algos_x86_basic_JG()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            // copy args
            { instruction::CPYIN, 0, 0, 0, 0, 0, 0},
            { instruction::CPYIN, 0, 0, 0, 1, 1, 0},
            { instruction::CPYIN, 0, 0, 0, 2, 2, 0},
            // jump to code at line given in third arg if arg0<arg1
            { instruction::JG, 0, 0, 0, 2, 1, 0},
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::CPYOUT, 0, 0, 0, 0, 0, 0},
            // line 6
            { instruction::CPYOUT, 0, 0, 0, 1, 1, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            100, 101, 6
        };
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

    /**
     * jump if lower or equal
    */
    bool launch_test_evo_algos_x86_basic_JLE()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            // copy args
            { instruction::CPYIN, 0, 0, 0, 0, 0, 0},
            { instruction::CPYIN, 0, 0, 0, 1, 1, 0},
            { instruction::CPYIN, 0, 0, 0, 2, 2, 0},
            // jump to code at line given in third arg if arg0>arg1
            { instruction::JLE, 0, 0, 0, 2, 1, 0},
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::CPYOUT, 0, 0, 0, 0, 2, 0},
            // line 6
            { instruction::CPYOUT, 0, 0, 0, 1, 1, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            100, 100, 6
        };
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
            std::cout << "Evo algos - x86 - basic - jumps - jle : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * jump if greater or equal
    */
    bool launch_test_evo_algos_x86_basic_JGE()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            // copy args
            { instruction::CPYIN, 0, 0, 0, 0, 0, 0},
            { instruction::CPYIN, 0, 0, 0, 1, 1, 0},
            { instruction::CPYIN, 0, 0, 0, 2, 2, 0},
            // jump to code at line given in third arg if arg0<arg1
            { instruction::JGE, 0, 0, 0, 2, 1, 0},
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::CPYOUT, 0, 0, 0, 0, 2, 0},
            // line 6
            { instruction::CPYOUT, 0, 0, 0, 1, 1, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            100, 100, 6
        };
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
            std::cout << "Evo algos - x86 - basic - jumps - jge : ";
            passed_print(is_passed);
        }

        return is_passed;
    }
 
    /**
     * relative positive jump if equal to 0
    */
    bool launch_test_evo_algos_x86_basic_JRE()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            // copy args
            { instruction::CPYIN, 0, 0, 0, 0, 0, 0},
            { instruction::CPYIN, 0, 0, 0, 1, 1, 0},
            { instruction::CPYIN, 0, 0, 0, 2, 2, 0},
            // jump to code at line given in first arg
            { instruction::JRE, 0, 0, 0, 2, 1, 1},
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::CPYOUT, 0, 0, 0, 0, 0, 0},
            // line 6
            { instruction::CPYOUT, 0, 0, 0, 1, 1, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            7, 667, 3
        };
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
            std::cout << "Evo algos - x86 - basic - jumps - jre : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * relative jump if lower
    */
    bool launch_test_evo_algos_x86_basic_JRL()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            // copy args
            { instruction::CPYIN, 0, 0, 0, 0, 0, 0},
            { instruction::CPYIN, 0, 0, 0, 1, 1, 0},
            { instruction::CPYIN, 0, 0, 0, 2, 2, 0},
            // jump to code at line given in third arg if arg0>arg1
            { instruction::JRL, 0, 0, 0, 2, 1, 0},
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::CPYOUT, 0, 0, 0, 0, 2, 0},
            // line 6
            { instruction::CPYOUT, 0, 0, 0, 1, 1, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            100, 99, 3
        };
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
            std::cout << "Evo algos - x86 - basic - jumps - jrl : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * relative jump if greater
    */
    bool launch_test_evo_algos_x86_basic_JRG()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            // copy args
            { instruction::CPYIN, 0, 0, 0, 0, 0, 0},
            { instruction::CPYIN, 0, 0, 0, 1, 1, 0},
            { instruction::CPYIN, 0, 0, 0, 2, 2, 0},
            // jump to code at line given in third arg if arg0<arg1
            { instruction::JRG, 0, 0, 0, 2, 1, 0},
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::CPYOUT, 0, 0, 0, 0, 2, 0},
            // line 6
            { instruction::CPYOUT, 0, 0, 0, 1, 1, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            100, 101, 3
        };
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
            std::cout << "Evo algos - x86 - basic - jumps - jrg : ";
            passed_print(is_passed);
        }

        return is_passed;
    }
 
    /**
     * relative jump if lower or equal
    */
    bool launch_test_evo_algos_x86_basic_JRLE()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            // copy args
            { instruction::CPYIN, 0, 0, 0, 0, 0, 0},
            { instruction::CPYIN, 0, 0, 0, 1, 1, 0},
            { instruction::CPYIN, 0, 0, 0, 2, 2, 0},
            // jump to code at line given in third arg if arg0>arg1
            { instruction::JRLE, 0, 0, 0, 2, 0, 1},
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::CPYOUT, 0, 0, 0, 0, 2, 0},
            // line 6
            { instruction::CPYOUT, 0, 0, 0, 1, 1, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            100, 100, 3
        };
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
            std::cout << "Evo algos - x86 - basic - jumps - jrle : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * relative jump if greater or equal
    */
    bool launch_test_evo_algos_x86_basic_JRGE()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            // copy args
            { instruction::CPYIN, 0, 0, 0, 0, 0, 0},
            { instruction::CPYIN, 0, 0, 0, 1, 1, 0},
            { instruction::CPYIN, 0, 0, 0, 2, 2, 0},
            // jump to code at line given in third arg if arg0<arg1
            { instruction::JRGE, 0, 0, 0, 2, 0, 1},
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::CPYOUT, 0, 0, 0, 0, 2, 0},
            // line 6
            { instruction::CPYOUT, 0, 0, 0, 1, 1, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            100, 100, 3
        };
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
            std::cout << "Evo algos - x86 - basic - jumps - jrge : ";
            passed_print(is_passed);
        }

        return is_passed;
    }
 
}