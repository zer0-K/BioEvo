//-------------------- EVOLUTIONARY ALGOS - X86 ALGO - BASIC - ARITHMETICS

#pragma once

#include <iostream>
#include <memory>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"

#include "../../Models/EvoAlgos/X86Algo/X86Algo.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_x86_basic_maths()
    {
        bool launch_test_evo_algos_x86_basic_INC(void);
        bool launch_test_evo_algos_x86_basic_DEC(void);
        bool launch_test_evo_algos_x86_basic_ADD(void);
        bool launch_test_evo_algos_x86_basic_SUB(void);
        bool launch_test_evo_algos_x86_basic_MUL(void);
        bool launch_test_evo_algos_x86_basic_DIV(void);
        bool launch_test_evo_algos_x86_basic_OPP(void);

        bool is_passed = true;

        std::cout << "Evo algos - x86 - basic - maths :" << std::endl;

        is_passed &= launch_test_evo_algos_x86_basic_INC(); 
        is_passed &= launch_test_evo_algos_x86_basic_DEC();
        is_passed &= launch_test_evo_algos_x86_basic_ADD();
        is_passed &= launch_test_evo_algos_x86_basic_SUB();
        is_passed &= launch_test_evo_algos_x86_basic_MUL();
        is_passed &= launch_test_evo_algos_x86_basic_DIV();
        is_passed &= launch_test_evo_algos_x86_basic_OPP();

        std::cout << "Evo algos - x86 - basic - maths : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * increment input
    */
    bool launch_test_evo_algos_x86_basic_INC()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            { instruction::CPYIN, 0, 0, 0, 10, 2, 0},
            { instruction::INC, 0, 0, 0, 10, 0, 0},
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

        if(res[0] != 0 || res[1] != 0 || res[2] != 0 || res[3] != 9 || res[4] != 0)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - maths - incrementation : ";
            passed_print(is_passed);
        }

        return is_passed;
    }    
    
    /**
     * decrement input
    */
    bool launch_test_evo_algos_x86_basic_DEC()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            { instruction::CPYIN, 0, 0, 0, 10, 2, 0},
            { instruction::DEC, 0, 0, 0, 10, 0, 0},
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

        if(res[0] != 0 || res[1] != 0 || res[2] != 0 || res[3] != 7 || res[4] != 0)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - maths - decrementation : ";
            passed_print(is_passed);
        }

        return is_passed;
    }    
    
    /**
     * addition
    */
    bool launch_test_evo_algos_x86_basic_ADD()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            { instruction::CPYIN, 0, 0, 0, 10, 2, 0},
            { instruction::CPYIN, 0, 0, 0, 11, 3, 0},
            { instruction::ADD, 0, 0, 0, 4, 11, 10},
            { instruction::CPYOUT, 0, 0, 0, 3, 4, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            0, 0, 8, 72, 0
        };
        algo->set_input(input);

        // output
        algo->set_output_size(5);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if(res[0] != 0 || res[1] != 0 || res[2] != 0 || res[3] != 80 || res[4] != 0)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - maths - addition : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * substraction
    */
    bool launch_test_evo_algos_x86_basic_SUB()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            { instruction::CPYIN, 0, 0, 0, 10, 2, 0},
            { instruction::CPYIN, 0, 0, 0, 11, 3, 0},
            { instruction::SUB, 0, 0, 0, 4, 10, 11},
            { instruction::CPYOUT, 0, 0, 0, 3, 4, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            0, 0, 8, 2, 0
        };
        algo->set_input(input);

        // output
        algo->set_output_size(5);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if(res[0] != 0 || res[1] != 0 || res[2] != 0 || res[3] != 6 || res[4] != 0)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - maths - substraction : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * multiplication
    */
    bool launch_test_evo_algos_x86_basic_MUL()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            { instruction::CPYIN, 0, 0, 0, 10, 2, 0},
            { instruction::CPYIN, 0, 0, 0, 11, 3, 0},
            { instruction::MUL, 0, 0, 0, 4, 11, 10},
            { instruction::CPYOUT, 0, 0, 0, 3, 4, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            0, 0, 8, 2, 0
        };
        algo->set_input(input);

        // output
        algo->set_output_size(5);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if(res[0] != 0 || res[1] != 0 || res[2] != 0 || res[3] != 16 || res[4] != 0)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - maths - multiplication : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * division
    */
    bool launch_test_evo_algos_x86_basic_DIV()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            { instruction::CPYIN, 0, 0, 0, 10, 2, 0},
            { instruction::CPYIN, 0, 0, 0, 11, 3, 0},
            { instruction::DIV, 0, 0, 0, 4, 10, 11},
            { instruction::CPYOUT, 0, 0, 0, 3, 4, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            0, 0, 21, 7, 0
        };
        algo->set_input(input);

        // output
        algo->set_output_size(5);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if(res[0] != 0 || res[1] != 0 || res[2] != 0 || res[3] != 3 || res[4] != 0)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - maths - division : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * division
    */
    bool launch_test_evo_algos_x86_basic_OPP()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            { instruction::CPYIN, 0, 0, 0, 4, 2, 0},
            { instruction::OPP, 0, 0, 0, 4, 0, 0},
            { instruction::CPYOUT, 0, 0, 0, 3, 4, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            0, 0, 21, 7, 0
        };
        algo->set_input(input);

        // output
        algo->set_output_size(5);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if(res[0] != 0 || res[1] != 0 || res[2] != 0 || res[3] != -21 || res[4] != 0)
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - maths - opposite : ";
            passed_print(is_passed);
        }

        return is_passed;
    }
}