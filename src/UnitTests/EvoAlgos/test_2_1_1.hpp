//-------------------- EVOLUTIONARY ALGOS - X86 ALGO - BASIC - MOVE

#pragma once

#include <iostream>
#include <memory>

#include "X86TesterHelper.hpp"
#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"

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


        //---------- CODE

        // copy input into data and copy data into output
        // absolute addrs
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::CPYOUT, 1, 0, 0, 3, 31415, 0 }           
        };
        // hybrid addrs
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 0, 0, 10, 31415, 0 },
            { instruction::CPYOUT, 1, 1, 0, 3, 10, 0 }        
        };
        // relative addrs
        std::vector<std::array<int,SIZE_INSTR>> code_2 { 
            { instruction::CPYIN, 1, 1, 0, 10, 2, 0 },
            { instruction::CPYOUT, 1, 1, 0, 3, 10, 0 }           
        };

        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1, code_2
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 0, 0, 7, 0, 0 };
        std::vector<int> input_1 = input_0;
        std::vector<int> input_2 = input_0;

        std::vector<std::vector<int>> inputs {
            input_0, input_1, input_2
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the molecular bodys should create
        std::vector<int> expected_out_0 { 0, 0, 0, 31415, 0 };
        std::vector<int> expected_out_1 = expected_out_0;
        std::vector<int> expected_out_2 { 0, 0, 0, input_2[2], 0 };

        std::vector<std::vector<int>> expected_outs {
            expected_out_0, expected_out_1, expected_out_2
        };


        //---------- EXECUTE

        for(int i=0; i<codes.size(); i++)
        {
            // set molecular body and execute
            algo->reset_data();
            algo->reset_code(codes[i]);

            algo->set_input(inputs[i]);
            algo->set_output_size(expected_outs[i].size());
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto out_res = algo->get_output();
            bool is_passed_i = x86_comp_output(expected_outs[i], out_res);
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - x86 - basic - move - copy in/out " << i << " : ";
                passed_print(is_passed_i);
            } 
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


        //---------- CODE

        // copy input into data and copy data into output
        // absolute addrs
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::MOV, 1, 0, 0, 20, 31415, 0},
            { instruction::CPYOUT, 1, 1, 0, 3, 20, 0}
        };
        // relative addrs
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 10, 2, 0},
            { instruction::MOV, 1, 1, 0, 20, 10, 0},
            { instruction::CPYOUT, 1, 1, 0, 3, 20, 0}
        };
        std::vector<std::array<int,SIZE_INSTR>> code_2 { 
            { instruction::CPYIN, 1, 1, 0, 5, 1, 0},
            { instruction::CPYIN, 1, 1, 0, 10, 2, 0},
            { instruction::MOV, 1, 2, 0, 20, 5, 0},
            { instruction::CPYOUT, 1, 1, 0, 3, 20, 0}
        };

        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1, code_2
        };


        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 0, 0, 7, 0, 0 };
        std::vector<int> input_1 = input_0;
        std::vector<int> input_2 { 0, 10, 7, 0, 0 };

        std::vector<std::vector<int>> inputs {
            input_0, input_1, input_2
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the molecular bodys should create
        std::vector<int> expected_out_0 { 0, 0, 0, 31415, 0 };
        std::vector<int> expected_out_1 { 0, 0, 0, input_1[2], 0 };
        std::vector<int> expected_out_2 { 0, 0, 0, input_2[2], 0 };

        std::vector<std::vector<int>> expected_outs {
            expected_out_0, expected_out_1, expected_out_2
        };


        //---------- EXECUTE

        for(int i=0; i<codes.size(); i++)
        {
            // set molecular body and execute
            algo->reset_data();
            algo->reset_code(codes[i]);

            algo->set_input(inputs[i]);
            algo->set_output_size(expected_outs[i].size());
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto out_res = algo->get_output();
            bool is_passed_i = x86_comp_output(expected_outs[i], out_res);
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - x86 - basic - move - move " << i << " : ";
                passed_print(is_passed_i);
            } 
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


        //---------- CODE

        // copy input into data and copy data into output
        // absolute addrs
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::CPY, 1, 0, 0, 20, 31415, 0},
            { instruction::CPYOUT, 1, 1, 0, 3, 20, 0}
        };
        // relative addrs
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 10, 2, 0},
            { instruction::CPY, 1, 1, 0, 20, 10, 0},
            { instruction::CPYOUT, 1, 1, 0, 3, 20, 0}
        };
        std::vector<std::array<int,SIZE_INSTR>> code_2 { 
            { instruction::CPYIN, 1, 1, 0, 5, 1, 0},
            { instruction::CPYIN, 1, 1, 0, 10, 2, 0},
            { instruction::CPY, 1, 2, 0, 20, 5, 0},
            { instruction::CPYOUT, 1, 1, 0, 3, 20, 0}
        };

        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1, code_2
        };


        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 0, 0, 7, 0, 0 };
        std::vector<int> input_1 = input_1;
        std::vector<int> input_2 { 0, 10, 7, 0, 0 };

        std::vector<std::vector<int>> inputs {
            input_0, input_1, input_2
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the molecular bodys should create
        std::vector<int> expected_out_0 { 0, 0, 0, 31415, 0 };
        std::vector<int> expected_out_1 { 0, 0, 0, input_1[2], 0 };
        std::vector<int> expected_out_2 { 0, 0, 0, input_2[2], 0 };

        std::vector<std::vector<int>> expected_outs {
            expected_out_0, expected_out_1, expected_out_2
        };


        //---------- EXECUTE

        for(int i=0; i<codes.size(); i++)
        {
            // set molecular body and execute
            algo->reset_data();
            algo->reset_code(codes[i]);

            algo->set_input(inputs[i]);
            algo->set_output_size(expected_outs[i].size());
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto out_res = algo->get_output();
            bool is_passed_i = x86_comp_output(expected_outs[i], out_res);
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - x86 - basic - move - copy " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - move - copy : ";
            passed_print(is_passed);
        } 

        return is_passed;

    }
    
}