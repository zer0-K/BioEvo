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
        bool launch_test_evo_algos_x86_basic_BEG(void);
        bool launch_test_evo_algos_x86_basic_HALT(void);

        bool is_passed = true;

        std::cout << "Evo algos - x86 - basic - other :" << std::endl;

        is_passed &= launch_test_evo_algos_x86_basic_XXX(); 
        is_passed &= launch_test_evo_algos_x86_basic_BEG(); 
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


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 1, 0},
            { instruction::XXX, 0, 0, 0, 1, 0, 0},
            { instruction::XXX, 0, 0, 0, 123456789, -123456789, 0}
        };
        // relative args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::XXX, 1, 1, 1, 0, 0, 0},
            { instruction::XXX, 1, 1, 1, 0, 1, 0},
            { instruction::XXX, 1, 1, 1, 1, 0, 0},
            { instruction::XXX, 1, 1, 1, 123456789, -123456789, 0}
        };        
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 667 };
        std::vector<int> input_1 = input_0;


        std::vector<std::vector<int>> inputs {
            input_0, input_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the genomes should create
        std::vector<int> expected_out_0 { 0 };
        std::vector<int> expected_out_1 { 0 };

        std::vector<std::vector<int>> expected_outs {
            expected_out_0, expected_out_1
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
            bool is_passed_i = x86_comp_output(expected_outs[i], out_res);
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - x86 - basic - other - xxx " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - other - xxx : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * begin program
    */
    bool launch_test_evo_algos_x86_basic_BEG()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::BEG, 0, 0, 0, -123456789, 123456789, 0},
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0},
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0}
        };
        // relative args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::BEG, 1, 1, 1, -123456789, 123456789, 0},
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0},
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0}
        };        
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 667 };
        std::vector<int> input_1 = input_0;


        std::vector<std::vector<int>> inputs {
            input_0, input_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the genomes should create
        std::vector<int> expected_out_0 { 667 };
        std::vector<int> expected_out_1 { 667 };

        std::vector<std::vector<int>> expected_outs {
            expected_out_0, expected_out_1
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
            bool is_passed_i = x86_comp_output(expected_outs[i], out_res);
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - x86 - basic - other - begin " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - other - begin : ";
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


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0},
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0},
            { instruction::HALT, 0, 0, 0, -123456789, 123456789, 0},
            { instruction::CPYIN, 1, 1, 0, 1, 1, 0},
            { instruction::CPYOUT, 1, 1, 0, 1, 1, 0}
        };
        // relative args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0},
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0},
            { instruction::HALT, 1, 1, 1, -123456789, 123456789, 0},
            { instruction::CPYIN, 1, 1, 0, 1, 1, 0},
            { instruction::CPYOUT, 1, 1, 0, 1, 1, 0}
        };        
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 667, 1 };
        std::vector<int> input_1 = input_0;


        std::vector<std::vector<int>> inputs {
            input_0, input_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the genomes should create
        std::vector<int> expected_out_0 { 667 };
        std::vector<int> expected_out_1 { 667 };

        std::vector<std::vector<int>> expected_outs {
            expected_out_0, expected_out_1
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
            bool is_passed_i = x86_comp_output(expected_outs[i], out_res);
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - x86 - basic - other - halt " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - other - halt : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

}