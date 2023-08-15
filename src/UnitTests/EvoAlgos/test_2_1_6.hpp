//-------------------- EVOLUTIONARY ALGOS - X86 ALGO - BASIC - IO

#pragma once

#include <iostream>
#include <memory>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"

#include "../../Models/EvoAlgos/X86Algo/X86Algo.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_x86_basic_io()
    {
        bool launch_test_evo_algos_x86_basic_io_cpyis(void);
        bool launch_test_evo_algos_x86_basic_io_setos(void);

        bool is_passed = true;

        std::cout << "Evo algos - x86 - basic - io :" << std::endl;

        is_passed &= launch_test_evo_algos_x86_basic_io_cpyis(); 
        is_passed &= launch_test_evo_algos_x86_basic_io_setos(); 

        std::cout << "Evo algos - x86 - basic - io : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief copy input size 
     */
    bool launch_test_evo_algos_x86_basic_io_cpyis()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            { instruction::CPYIS, 0, 0, 0, 0, 0, 0},
            { instruction::CPYOUT, 0, 0, 0, 0, 0, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            1000, 3, 3, 3, 3
        };
        algo->set_input(input);

        // output
        algo->set_output_size(1);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if( res[0] != input.size() )
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - io - cpyis: ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief set output size 
     */
    bool launch_test_evo_algos_x86_basic_io_setos()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            { instruction::CPYIN, 0, 0, 0, 0, 0, 0},
            { instruction::SETOS, 0, 0, 0, 0, 0, 0}
        };
        algo->set_code(code, 0);

        // input 
        std::vector<int> input {
            100 
        };
        algo->set_input(input);

        // output
        algo->set_output_size(1);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if( res.size() != input[0] )
        {
            is_passed = false;
        }

        // now, reduce output size
        input[0] = 10;
        algo->set_input(input);
        algo->exec(std::vector<sp_entity>(0));
        res = algo->get_output();

        if( res.size() != input[0] )
        {
            is_passed = false;
        }


        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - io - setos: ";
            passed_print(is_passed);
        }

        return is_passed;
    }


}