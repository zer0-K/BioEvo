//-------------------- EVOLUTIONARY ALGOS - EVO X - genes - mutations

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"

#include "../../Models/EvoAlgos/X86Algo/EvoX.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_evox_genes_mutations()
    {
        bool test_evo_algos_evox_genes_mutations_insertion(void);
        bool test_evo_algos_evox_genes_mutations_deletion(void);
        bool test_evo_algos_evox_genes_mutations_substitution(void);

        bool is_passed = true;

        std::cout << "Evo algos - evox - genes - mutations :" << std::endl;
 
        is_passed &= test_evo_algos_evox_genes_mutations_insertion();
        is_passed &= test_evo_algos_evox_genes_mutations_deletion();
        is_passed &= test_evo_algos_evox_genes_mutations_substitution();

        std::cout << "Evo algos - evox - genes - mutations : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief gene insertion
    */
    bool test_evo_algos_evox_genes_mutations_insertion()
    {
        bool is_passed = true;

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();

        //---------- GENOME

        // genomes coding simple programs
        // 
        // insert args as genes
        std::vector<int> genome_1 { 
            instruction::CPYIN, 0, 0,   // 0
            instruction::CPYIN, 1, 1,   // 1
            instruction::CPYIN, 2, 2,   // 2
            instruction::GINS, 3, 2,    // 3 insert 3rd gene arg at 0
            instruction::GINS, 3, 1,    // 4 insert 2nd gene arg at 0
            instruction::GINS, 3, 0,    // 5 insert 1st gene arg at 0
            instruction::CPYOUT, 0, 4   // 6 copy val at 4
        };

        std::vector<std::vector<int>> genomes {
            genome_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_1_1 {
            instruction::INC, 4, 4
        };
        std::vector<int> input_1_2 = input_1_1;
        std::vector<int> input_1_3 = input_1_1;
        std::vector<int> input_1_4 = input_1_1;

        std::vector<std::vector<int>> inputs_1 {
            input_1_1, input_1_2, input_1_3, input_1_4
        };

        std::vector<std::vector<std::vector<int>>> inputs {
            inputs_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the genomes should create
        std::vector<int> expected_out_1_1 { 0 };
        std::vector<int> expected_out_1_2 { 1 };
        std::vector<int> expected_out_1_3 { 3 };
        std::vector<int> expected_out_1_4 { 6 };

        std::vector<std::vector<int>> expected_outs_1 {
            expected_out_1_1, expected_out_1_2, expected_out_1_3, expected_out_1_4 
        };

        std::vector<std::vector<std::vector<int>>> expected_outs {
            expected_outs_1 
        };

        // output
        
        //---------- EXECUTE

        for(int i=0; i<expected_outs.size(); i++)
        {
            // set genome and execute
            algo->set_genes(genomes[i]);
            algo->reset_data();

            // for more accurate debug in case a unit test does not pass
            bool is_passed_i = true;

            for(int j=0; j<expected_outs[i].size(); j++)
            {
                algo->set_input_size(inputs[i][j].size());
                algo->set_output_size(expected_outs[i][j].size());

                algo->set_input(inputs[i][j]);
                algo->exec(std::vector<sp_entity>(0));

                // check result
                auto out_res = algo->get_output();
                bool is_passed_i_j = x86_comp_output(expected_outs[i][j], out_res);
                is_passed_i &= is_passed_i_j;
                is_passed &= is_passed_i; 

                if(verbose_unit_tests_1)
                {
                    std::cout << "Evo algos - evox - genes - mutations - insertion "
                              << i << " - " << j << ": ";
                    passed_print(is_passed_i_j);
                } 
            }

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - evox - genes - mutations - insertion " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - genes - mutations - insertion " << " : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 

    /**
     * @brief gene deletion
    */
    bool test_evo_algos_evox_genes_mutations_deletion()
    {     bool is_passed = true;

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();

        //---------- GENOME

        // genomes coding simple programs
        // 
        // insert args as genes
        std::vector<int> genome_1 { 
            instruction::INC, 0, 0,     // 0
            instruction::INC, 0, 0,     // 1
            instruction::INC, 0, 0,     // 2
            instruction::INC, 0, 0,     // 3
            instruction::INC, 0, 0,     // 4
            instruction::GDEL, 1, 1,    // 5 delete gene at 0 (INC)
            instruction::GDEL, 1, 1,    // 6 delete gene at 0 (INC)
            instruction::GDEL, 1, 1,    // 7 delete gene at 0 (INC)
            instruction::INC, 0, 0,     // 8
            instruction::CPYOUT, 0, 0   // 9 copy val at 0
        };
        std::vector<int> genome_2 { 
            instruction::INC, 0, 0,     // 0
            instruction::INC, 0, 0,     // 1
            instruction::INC, 0, 0,     // 2
            instruction::INC, 0, 0,     // 3
            instruction::INC, 0, 0,     // 4
            instruction::GDELW, 1, 1,   // 5 delete gene at 0 (INC)
            instruction::INC, 0, 0,     // 6
            instruction::CPYOUT, 0, 0   // 7 copy val at 0
        };

        std::vector<std::vector<int>> genomes {
            genome_1, genome_2
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        // 1
        std::vector<int> input_1_1 { };
        std::vector<int> input_1_2 = input_1_1;
        std::vector<int> input_1_3 = input_1_1;
        std::vector<int> input_1_4 = input_1_1;
        std::vector<int> input_1_5 = input_1_1;
        std::vector<std::vector<int>> inputs_1 {
            input_1_1, input_1_2, input_1_3, input_1_4, input_1_5        
        };
        // 2
        std::vector<int> input_2_1 { };
        std::vector<int> input_2_2 = input_1_1;
        std::vector<int> input_2_3 = input_1_1;
        std::vector<int> input_2_4 = input_1_1;
        std::vector<int> input_2_5 = input_1_1;
        std::vector<int> input_2_6 = input_1_1;
        std::vector<int> input_2_7 = input_1_1;
        std::vector<std::vector<int>> inputs_2 {
            input_2_1, input_2_2, input_2_3, input_2_4, input_2_5,
            input_2_6, input_2_7
        };


        std::vector<std::vector<std::vector<int>>> inputs {
            inputs_1, inputs_2
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the genomes should create
        // 1
        std::vector<int> expected_out_1_1 { 6 };
        std::vector<int> expected_out_1_2 { 11 };
        std::vector<int> expected_out_1_3 { 15 };
        std::vector<int> expected_out_1_4 { 18 };
        std::vector<int> expected_out_1_5 { 20 };
        std::vector<std::vector<int>> expected_outs_1 {
            expected_out_1_1, expected_out_1_2, expected_out_1_3, expected_out_1_4, expected_out_1_5
        };
        // 2
        std::vector<int> expected_out_2_1 { 6 };
        std::vector<int> expected_out_2_2 { 11 };
        std::vector<int> expected_out_2_3 { 15 };
        std::vector<int> expected_out_2_4 { 18 };
        std::vector<int> expected_out_2_5 { 20 };
        std::vector<int> expected_out_2_6 { 21 };
        std::vector<int> expected_out_2_7 { 22 };
        std::vector<std::vector<int>> expected_outs_2 {
            expected_out_2_1, expected_out_2_2, expected_out_2_3, expected_out_2_4, expected_out_2_5,
            expected_out_2_6, expected_out_2_7
        };


        std::vector<std::vector<std::vector<int>>> expected_outs {
            expected_outs_1, expected_outs_2 
        };

        // output
        
        //---------- EXECUTE

        for(int i=0; i<expected_outs.size(); i++)
        {
            // set genome and execute
            algo->set_genes(genomes[i]);
            algo->reset_data();

            // for more accurate debug in case a unit test does not pass
            bool is_passed_i = true;

            for(int j=0; j<expected_outs[i].size(); j++)
            {
                algo->set_input_size(inputs[i][j].size());
                algo->set_output_size(expected_outs[i][j].size());

                algo->set_input(inputs[i][j]);
                algo->exec(std::vector<sp_entity>(0));

                // check result
                auto out_res = algo->get_output();
                bool is_passed_i_j = x86_comp_output(expected_outs[i][j], out_res);
                is_passed_i &= is_passed_i_j;
                is_passed &= is_passed_i; 

                if(verbose_unit_tests_1)
                {
                    std::cout << "Evo algos - evox - genes - mutations - deletion "
                              << i << " - " << j << ": ";
                    passed_print(is_passed_i_j);
                } 
            }

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - evox - genes - mutations - deletion " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - genes - mutations - deletion " << " : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 

    /**
     * @brief gene substitution
    */
    bool test_evo_algos_evox_genes_mutations_substitution()
    {
        bool is_passed = true;

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();

        //---------- GENOME

        // genomes coding simple programs
        // 
        // SET 
        std::vector<int> genome_1 { 
            instruction::CPYIN, 0, 0,   // 0
            instruction::CPYIN, 1, 1,   // 1
            instruction::CPYIN, 2, 2,   // 2
            instruction::CPYIN, 3, 3,   // 3
            instruction::CPY, 10, 0,    // 4
            instruction::GSET, 0, 1,    // 5
            instruction::CPYOUT, 0, 10  // 6
        };
        // GADD
        std::vector<int> genome_2 { 
            instruction::CPYIN, 0, 0,   // 0
            instruction::CPYIN, 1, 1,   // 1
            instruction::CPYIN, 2, 2,   // 2
            instruction::CPYIN, 3, 3,   // 3
            instruction::CPY, 10, 0,    // 4
            instruction::GADD, 0, 1,    // 5
            instruction::CPYOUT, 0, 10  // 6
        };
 
        std::vector<std::vector<int>> genomes {
            genome_1, genome_2
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        // SET
        std::vector<int> input_1_1 { 14, 1, 100, 667 };
        std::vector<int> input_1_2 { 14, 2, 100, 667 };
        std::vector<int> input_1_3 { 14, 3, 100, 667 };
        std::vector<int> input_1_4 { 14, 4, 100, 667 };
        std::vector<std::vector<int>> inputs_1 {
            input_1_1, input_1_2, input_1_3, input_1_4
        };
        // GADD
        std::vector<int> input_2_1 { 14, 1, 100, 667 };
        std::vector<int> input_2_2 { 14, 1, 100, 667 };
        std::vector<int> input_2_3 { 14, 1, 100, 667 };
        std::vector<int> input_2_4 { 14, 1, 100, 667 };
        std::vector<std::vector<int>> inputs_2 {
            input_2_1, input_2_2, input_2_3, input_2_4
        };

        std::vector<std::vector<std::vector<int>>> inputs {
            inputs_1, inputs_2
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the genomes should create
        // SET
        std::vector<int> expected_out_1_1 { 14 };
        std::vector<int> expected_out_1_2 { 2 };
        std::vector<int> expected_out_1_3 { 100 };
        std::vector<int> expected_out_1_4 { 667 };
        std::vector<std::vector<int>> expected_outs_1 {
            expected_out_1_1, expected_out_1_2, expected_out_1_3, expected_out_1_4 
        };
        // GADD
        std::vector<int> expected_out_2_1 { 14 };
        std::vector<int> expected_out_2_2 { 1 };
        std::vector<int> expected_out_2_3 { 100 };
        std::vector<int> expected_out_2_4 { 667 };
        std::vector<std::vector<int>> expected_outs_2 {
            expected_out_2_1, expected_out_2_2, expected_out_2_3, expected_out_2_4 
        };

        std::vector<std::vector<std::vector<int>>> expected_outs {
            expected_outs_1, expected_outs_2
        };

        // output
        
        //---------- EXECUTE

        for(int i=0; i<expected_outs.size(); i++)
        {
            // set genome and execute
            algo->set_genes(genomes[i]);
            algo->reset_data();

            // for more accurate debug in case a unit test does not pass
            bool is_passed_i = true;

            for(int j=0; j<expected_outs[i].size(); j++)
            {
                algo->set_input_size(inputs[i][j].size());
                algo->set_output_size(expected_outs[i][j].size());

                algo->set_input(inputs[i][j]);
                algo->exec(std::vector<sp_entity>(0));

                // check result
                auto out_res = algo->get_output();
                bool is_passed_i_j = x86_comp_output(expected_outs[i][j], out_res);
                is_passed_i &= is_passed_i_j;
                is_passed &= is_passed_i; 

                if(verbose_unit_tests_1)
                {
                    std::cout << "Evo algos - evox - genes - mutations - substitution "
                              << i << " - " << j << ": ";
                    passed_print(is_passed_i_j);
                } 
            }

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - evox - genes - mutations - substitution " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - genes - mutations - substitution " << " : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 


}