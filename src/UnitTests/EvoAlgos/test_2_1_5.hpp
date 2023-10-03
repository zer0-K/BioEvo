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
        std::vector<std::array<int,SIZE_INSTR>> code {
            { instruction::CPYIN, 0, 0, 0, 0, 0, 0},
            { instruction::CPYIN, 0, 0, 0, 1, 1, 0},
            { instruction::CPY, 0, 0, 0, 2, 0, 0},
            { instruction::RN, 0, 0, 0, 4, 4, 0},
            { instruction::ADD, 0, 0, 0, 3, 4, 0},
            { instruction::DEC, 0, 0, 0, 2, 2, 0},
            { instruction::JG, 0, 0, 0, 1, 2, 0},
            { instruction::DIV, 0, 0, 0, 3, 0, 0},
            { instruction::CPYOUT, 0, 0, 0, 0, 3, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            1000, 3
        };
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


        //---------- CODE

        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::CPYIN, 1, 1, 0, 1, 1, 0 },
            { instruction::CPYIN, 1, 1, 0, 2, 2, 0 },
            { instruction::CPYIN, 1, 1, 0, 3, 3, 0 },
            { instruction::CPY, 1, 1, 0, 4, 0, 0 },
            { instruction::RUI, 1, 1, 1, 5, 1, 2 },
            { instruction::ADD, 1, 1, 1, 6, 6, 5 },
            { instruction::DEC, 1, 0, 0, 4, 0, 0 },
            { instruction::JG, 1, 1, 1, 3, 4, 7 },
            { instruction::DIV, 1, 1, 1, 6, 6, 0 },
            { instruction::CPYOUT, 1, 1, 0, 0, 6, 0 }
        };
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 1000, 11, 16, 5 };

        std::vector<std::vector<int>> inputs {
            input_0
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the genomes should create
        std::vector<int> expected_out_0 { 13 };

        std::vector<std::vector<int>> expected_outs {
            expected_out_0
        };


        //---------- EXECUTE

        for(int i=0; i<codes.size(); i++)
        {
            // set genome and execute
            algo->reset_data();
            algo->reset_code(codes[i]);

            algo->set_input(inputs[i]);
            algo->set_output_size(expected_outs[i].size());
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto out_res = algo->get_output();

            // result is 13.666 but since it's ints...
            bool is_passed_i = true;
            if( std::abs(out_res[0]-13) > 0.01 )
            {
                is_passed_i = false;
            }
            
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - x86 - basic - random - uniform " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - random - uniform : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

}