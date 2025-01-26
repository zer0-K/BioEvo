//-------------------- EVOLUTIONARY ALGOS - EVO X - PHENOTYPIC BODY - BASIC

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"

#include "../../Models/EvoAlgos/X86Algo/EvoX.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_evox_phenotypic_body_basic()
    {
        bool test_evox_phenotypic_body_basic_empty(void);
        bool test_evox_phenotypic_body_basic_incomplete(void);
        bool test_evox_phenotypic_body_basic_simple(void);
        bool test_evox_phenotypic_body_basic_read(void);

        bool is_passed = true;

        std::cout << "Evo algos - evox - phenotypic body - basic :" << std::endl;

        is_passed &= test_evox_phenotypic_body_basic_empty();
        is_passed &= test_evox_phenotypic_body_basic_incomplete();
        is_passed &= test_evox_phenotypic_body_basic_simple();
        is_passed &= test_evox_phenotypic_body_basic_read();

        std::cout << "Evo algos - evox - phenotypic body - basic : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * Test phenotypic bodys with empty instructions
    */
    bool test_evox_phenotypic_body_basic_empty()
    {
        bool is_passed = true;

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();

        //---------- PHENOTYPIC BODYS

        // several phenotypic bodies coding empty programs
        std::vector<int> phenotypic_body_1 {};
        std::vector<int> phenotypic_body_2 { 
            instruction::XXX, 0, 0, 0, 1, 0, 0
        };
        std::vector<int> phenotypic_body_3 {
            instruction::HALT, 0, 0, 0, 2, 0, 0
        };
        std::vector<int> phenotypic_body_4 {
            instruction::BEG, 0, 0, 0, 2, 0, 0
        };
        std::vector<int> phenotypic_body_5 {
            instruction::BEG, 0, 0, 0, 2, 0, 0,
            instruction::HALT, 0, 0, 0, 2, 0, 0,
        };
        std::vector<int> phenotypic_body_6 {
            instruction::XXX, 0, 0, 0, 3, 0, 0,
            instruction::XXX, 0, 0, 0, 4, 0, 0,
            instruction::HALT, 0, 0, 0, 5, 0, 0
        };

        std::vector<std::vector<int>> phenotypic_bodies {
            phenotypic_body_1, phenotypic_body_2, phenotypic_body_3, phenotypic_body_4, phenotypic_body_5, 
            phenotypic_body_6
        };

        //---------- EXPECTED CODES

        // the expected codes the phenotypic bodys should create
        std::vector<std::array<int,SIZE_INSTR>> expected_code_1 {
            { instruction::HALT, 0, 0, 0, 0, 0, 0 }
        };
        std::vector<std::array<int,SIZE_INSTR>> expected_code_2 {
            { instruction::XXX, 0, 0, 0, 1, 0, 0 }
        };
        std::vector<std::array<int,SIZE_INSTR>> expected_code_3 {
            { instruction::HALT, 0, 0, 0, 2, 0, 0 }
        };
        std::vector<std::array<int,SIZE_INSTR>> expected_code_4 {
            { instruction::BEG, 0, 0, 0, 2, 0, 0 }
        };
        std::vector<std::array<int,SIZE_INSTR>> expected_code_5 {
            { instruction::BEG, 0, 0, 0, 2, 0, 0 },
            { instruction::HALT, 0, 0, 0, 2, 0, 0 }
        };
        std::vector<std::array<int,SIZE_INSTR>> expected_code_6 {
            { instruction::XXX, 0, 0, 0, 3, 0, 0 },
            { instruction::XXX, 0, 0, 0, 4, 0, 0 },
            { instruction::HALT, 0, 0, 0, 5, 0, 0 }
        };

        std::vector<std::vector<std::array<int,SIZE_INSTR>>> expected_codes {
            expected_code_1, expected_code_2, expected_code_3, expected_code_4, expected_code_5,
            expected_code_6
        };

        //---------- IN/OUT

        // input (here, same for all tests, size does not matter)
        std::vector<int> input {
            1, 2
        };
        algo->set_input(input);

        // output (size does not matter)
        algo->set_output_size(SIZE_INSTR);


        //---------- EXECUTE

        for(int i=0; i<expected_codes.size(); i++)
        {
            // set phenotypic body and execute
            algo->set_phenotypic_body(phenotypic_bodies[i]);
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto code_res = algo->get_code();
            bool ok = x86_comp_code(expected_codes[i], code_res);
            is_passed &= ok;

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - evox - phenotypic body - basic - empty " << i << " : ";
                passed_print(ok);
            }
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - phenotypic body - basic - empty : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * Test phenotypic bodys encoding incomplete instructions (at the end)
    */
    bool test_evox_phenotypic_body_basic_incomplete()
    {
        bool is_passed = true;

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();

        //---------- PHENOTYPIC BODYS

        // several phenotypic bodies coding incomplete instructions
        std::vector<int> phenotypic_body_1 { 
            instruction::XXX, 0, 0, 0, 1, 0
        };
        std::vector<int> phenotypic_body_2 {
            9999
        };
        std::vector<int> phenotypic_body_3 {
            instruction::XXX, 0, 0, 0, 2, 0, 0,
            instruction::XXX, 0, 0, 0, 3, 0, 0
        };
        std::vector<int> phenotypic_body_4 {
            instruction::XXX, 0, 0, 0, 2, 0, 0,
            instruction::XXX, 0, 0, 0, 3, 0, 0,
            999
        };

        std::vector<std::vector<int>> phenotypic_bodies {
            phenotypic_body_1, phenotypic_body_2, phenotypic_body_3, phenotypic_body_4
        };

        //---------- EXPECTED CODES

        // the expected codes the phenotypic bodys should create
        std::vector<std::array<int,SIZE_INSTR>> expected_code_1 {
            { instruction::HALT, 0, 0, 0, 0, 0, 0 }
        };
        std::vector<std::array<int,SIZE_INSTR>> expected_code_2 {
            { instruction::HALT, 0, 0, 0, 0, 0, 0 }
        };
        std::vector<std::array<int,SIZE_INSTR>> expected_code_3 {
            { instruction::XXX, 0, 0, 0, 2, 0, 0 },
            { instruction::XXX, 0, 0, 0, 3, 0, 0 }
        };
        std::vector<std::array<int,SIZE_INSTR>> expected_code_4 {
            { instruction::XXX, 0, 0, 0, 2, 0, 0 },
            { instruction::XXX, 0, 0, 0, 3, 0, 0 }
        };

        std::vector<std::vector<std::array<int,SIZE_INSTR>>> expected_codes {
            expected_code_1, expected_code_2, expected_code_3, expected_code_4
        };

        //---------- IN/OUT

        // input (here, same for all tests, size does not matter)
        std::vector<int> input {
            1, 2
        };
        algo->set_input_size(input.size());
        algo->set_input(input);

        // output (size does not matter)
        algo->set_output_size(1);


        //---------- EXECUTE

        for(int i=0; i<expected_codes.size(); i++)
        {
            // set phenotypic body and execute
            algo->set_phenotypic_body(phenotypic_bodies[i]);
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto code_res = algo->get_code();
            bool ok = x86_comp_code(expected_codes[i], code_res);
            is_passed &= ok;

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - evox - phenotypic body - basic - incomplete " << i << " : ";
                passed_print(ok);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - phenotypic body - basic - incomplete : ";
            passed_print(is_passed);
        }

        return is_passed;
    }
        
    /**
     * Simple genetic program
    */
    bool test_evox_phenotypic_body_basic_simple()
    {
        bool is_passed = true;

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();

        //---------- PHENOTYPIC BODY

        // phenotypic bodys coding simple programs
        // 
        std::vector<int> phenotypic_body_1 { 
            instruction::BEG, 0, 0, 0, 0, 0, 0,     // 0
            instruction::CPYIN, 1, 1, 0, 0, 0, 0,   // 1
            instruction::INC, 1, 0, 0, 1, 0, 0,     // 2
            instruction::INC, 1, 0, 0, 1, 0, 0,     // 3
            instruction::INC, 1, 0, 0, 1, 0, 0,     // 4
            instruction::INC, 1, 0, 0, 3, 0, 0,     // 5
            instruction::JRE, 1, 1, 1, 1, 0, 4,     // 6
            instruction::DEC, 1, 0, 0, 0, 0, 0,     // 7
            instruction::JRS, 1, 1, 1, 1, 0, 0,     // 8
            instruction::DEC, 1, 0, 0, 3, 0, 0,     // 9
            instruction::CPYOUT, 1, 1, 0, 0, 3, 0,  // 10
            instruction::HALT, 0, 0, 0, 0, 0, 0
        };

        std::vector<std::vector<int>> phenotypic_bodies {
            phenotypic_body_1
        };

        //---------- EXPECTED OUTPUT

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_1 {
            10
        };

        std::vector<std::vector<int>> expected_outs {
            expected_out_1
        };

        //---------- IN/OUT

        // input (here, same for all tests for simplicity)
        std::vector<int> input {
            10
        };
        algo->set_input_size(input.size());
        algo->set_input(input);

        // output
        algo->set_output_size(1);


        //---------- EXECUTE

        for(int i=0; i<expected_outs.size(); i++)
        {
            // set phenotypic body and execute
            algo->set_phenotypic_body(phenotypic_bodies[i]);
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto out_res = algo->get_output();
            bool ok = x86_comp_output(expected_outs[i], out_res);
            is_passed &= ok;

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - evox - phenotypic body - basic - simple " << i << " : ";
                passed_print(ok);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - phenotypic body - basic - simple : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * Read phenotypic body
    */
    bool test_evox_phenotypic_body_basic_read()
    {
        bool is_passed = true;

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();

        //---------- PHENOTYPIC BODY

        // phenotypic bodys coding simple programs
        // 
        std::vector<int> phenotypic_body_1 { 
            instruction::BEG, 0, 0, 0, 0, 0, 0,     // 0
            instruction::GR, 1, 1, 0, 1, 21, 0,     // 1
            instruction::CPYOUT, 1, 1, 0, 0, 1, 0,  // 2
            instruction::HALT, 0, 0, 0, 0, 0, 0     // 3
        };

        std::vector<std::vector<int>> phenotypic_bodies {
            phenotypic_body_1
        };

        //---------- EXPECTED OUTPUT

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_1 {
            instruction::HALT
        };

        std::vector<std::vector<int>> expected_outs {
            expected_out_1
        };

        //---------- IN/OUT

        // input (here, same for all tests for simplicity)
        std::vector<int> input {
            
        };
        algo->set_input_size(input.size());
        algo->set_input(input);

        // output
        algo->set_output_size(1);


        //---------- EXECUTE

        for(int i=0; i<expected_outs.size(); i++)
        {
            // set phenotypic body and execute
            algo->set_phenotypic_body(phenotypic_bodies[i]);
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto out_res = algo->get_output();
            bool ok = x86_comp_output(expected_outs[i], out_res);
            is_passed &= ok;

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - evox - phenotypic body - basic - read " << i << " : ";
                passed_print(ok);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - phenotypic body - basic - read : ";
            passed_print(is_passed);
        }

        return is_passed;
    }
     
}