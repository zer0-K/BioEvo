//-------------------- EVOLUTIONARY ALGOS - EVO X - GENES - BASIC

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"

#include "../../Models/EvoAlgos/X86Algo/EvoX.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_evox_genes_basic()
    {
        bool test_evox_genes_basic_empty(void);
        bool test_evox_genes_basic_incomplete(void);
        bool test_evox_genes_basic_simple(void);
        bool test_evox_genes_basic_read(void);

        bool is_passed = true;

        std::cout << "Evo algos - evox - genes - basic :" << std::endl;

        is_passed &= test_evox_genes_basic_empty();
        is_passed &= test_evox_genes_basic_incomplete();
        is_passed &= test_evox_genes_basic_simple();
        is_passed &= test_evox_genes_basic_read();

        std::cout << "Evo algos - evox - genes - basic : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * Test genomes with empty instructions
    */
    bool test_evox_genes_basic_empty()
    {
        bool is_passed = true;

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();

        //---------- GENOMES

        // several genomes coding empty programs
        std::vector<int> genome_1 {};
        std::vector<int> genome_2 { 
            instruction::XXX, 0, 0, 0, 1, 0, 0
        };
        std::vector<int> genome_3 {
            instruction::HALT, 0, 0, 0, 2, 0, 0
        };
        std::vector<int> genome_4 {
            instruction::BEG, 0, 0, 0, 2, 0, 0
        };
        std::vector<int> genome_5 {
            instruction::BEG, 0, 0, 0, 2, 0, 0,
            instruction::HALT, 0, 0, 0, 2, 0, 0,
        };
        std::vector<int> genome_6 {
            instruction::XXX, 0, 0, 0, 3, 0, 0,
            instruction::XXX, 0, 0, 0, 4, 0, 0,
            instruction::HALT, 0, 0, 0, 5, 0, 0
        };

        std::vector<std::vector<int>> genomes {
            genome_1, genome_2, genome_3, genome_4, genome_5, 
            genome_6
        };

        //---------- EXPECTED CODES

        // the expected codes the genomes should create
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
            // set genome and execute
            algo->set_genes(genomes[i]);
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto code_res = algo->get_code();
            bool ok = x86_comp_code(expected_codes[i], code_res);
            is_passed &= ok;

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - evox - genes - basic - empty " << i << " : ";
                passed_print(ok);
            }
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - genes - basic - empty : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * Test genomes encoding incomplete instructions (at the end)
    */
    bool test_evox_genes_basic_incomplete()
    {
        bool is_passed = true;

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();

        //---------- GENOMES

        // several genomes coding incomplete instructions
        std::vector<int> genome_1 { 
            instruction::XXX, 0, 0, 0, 1, 0
        };
        std::vector<int> genome_2 {
            9999
        };
        std::vector<int> genome_3 {
            instruction::XXX, 0, 0, 0, 2, 0, 0,
            instruction::XXX, 0, 0, 0, 3, 0, 0
        };
        std::vector<int> genome_4 {
            instruction::XXX, 0, 0, 0, 2, 0, 0,
            instruction::XXX, 0, 0, 0, 3, 0, 0,
            999
        };

        std::vector<std::vector<int>> genomes {
            genome_1, genome_2, genome_3, genome_4
        };

        //---------- EXPECTED CODES

        // the expected codes the genomes should create
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
            // set genome and execute
            algo->set_genes(genomes[i]);
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto code_res = algo->get_code();
            bool ok = x86_comp_code(expected_codes[i], code_res);
            is_passed &= ok;

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - evox - genes - basic - incomplete " << i << " : ";
                passed_print(ok);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - genes - basic - incomplete : ";
            passed_print(is_passed);
        }

        return is_passed;
    }
        
    /**
     * Simple genetic program
    */
    bool test_evox_genes_basic_simple()
    {
        bool is_passed = true;

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();

        //---------- GENOME

        // genomes coding simple programs
        // 
        std::vector<int> genome_1 { 
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

        std::vector<std::vector<int>> genomes {
            genome_1
        };

        //---------- EXPECTED OUTPUT

        // the expected outputs of the code the genomes should create
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
            // set genome and execute
            algo->set_genes(genomes[i]);
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto out_res = algo->get_output();
            bool ok = x86_comp_output(expected_outs[i], out_res);
            is_passed &= ok;

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - evox - genes - basic - simple " << i << " : ";
                passed_print(ok);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - genes - basic - simple : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * Read genes
    */
    bool test_evox_genes_basic_read()
    {
        bool is_passed = true;

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();

        //---------- GENOME

        // genomes coding simple programs
        // 
        std::vector<int> genome_1 { 
            instruction::BEG, 0, 0, 0, 0, 0, 0,     // 0
            instruction::GR, 1, 1, 0, 1, 21, 0,     // 1
            instruction::CPYOUT, 1, 1, 0, 0, 1, 0,  // 2
            instruction::HALT, 0, 0, 0, 0, 0, 0     // 3
        };

        std::vector<std::vector<int>> genomes {
            genome_1
        };

        //---------- EXPECTED OUTPUT

        // the expected outputs of the code the genomes should create
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
            // set genome and execute
            algo->set_genes(genomes[i]);
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto out_res = algo->get_output();
            bool ok = x86_comp_output(expected_outs[i], out_res);
            is_passed &= ok;

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - evox - genes - basic - read " << i << " : ";
                passed_print(ok);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - genes - basic - read : ";
            passed_print(is_passed);
        }

        return is_passed;
    }
     
}