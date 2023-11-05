//-------------------- EVOLUTIONARY ALGOS - EVO X - GENES - EXEC

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"

#include "../../Models/EvoAlgos/X86Algo/EvoX.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_evox_genes_exec()
    {
        bool test_evo_algos_evox_genes_exec_simple(void);

        bool is_passed = true;

        std::cout << "Evo algos - evox - genes - exec :" << std::endl;
 
        is_passed &= test_evo_algos_evox_genes_exec_simple();

        std::cout << "Evo algos - evox - genes - exec : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief exec genome dynamically
    */
    bool test_evo_algos_evox_genes_exec_simple()
    {
        bool is_passed = true;

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();

        //---------- GENOME

        // genomes coding simple programs
        // 
        std::vector<int> genome_1 { 
            instruction::INC, 1, 0, 0, 5, 0, 0,
            instruction::EXEC, 0, 0, 0, 0, 1, 0,
            instruction::CPYOUT, 1, 1, 0, 0, 5, 0,
            instruction::HALT, 0, 0, 0, 0, 0, 0
        };
        std::vector<int> genome_2 {
            instruction::XXX, 0, 0, 0, 0, 0, 0,
            instruction::INC, 1, 0, 0, 5, 0, 0,
            instruction::INC, 1, 0, 0, 5, 0, 0,
            instruction::EXEC, 0, 0, 0, 1, 2, 0,
            instruction::CPYOUT, 1, 1, 0, 0, 5, 0,
            instruction::HALT, 0, 0, 0, 0, 0, 0
        };

        std::vector<std::vector<int>> genomes {
            genome_1, genome_2
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_1_1 {};
        std::vector<int> input_1_2 = input_1_1;
        std::vector<int> input_1_3 = input_1_1;

        std::vector<std::vector<int>> inputs_1 {
            input_1_1, input_1_2, input_1_3
        };
        std::vector<std::vector<int>> inputs_2 = inputs_1;

        std::vector<std::vector<std::vector<int>>> inputs {
            inputs_1, inputs_2
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the genomes should create
        std::vector<int> expected_out_1_1 { 2 };
        std::vector<int> expected_out_1_2 { 4 };
        std::vector<int> expected_out_1_3 { 6 };

        std::vector<std::vector<int>> expected_outs_1 {
            expected_out_1_1, expected_out_1_2, expected_out_1_3
        };

        std::vector<int> expected_out_2_1 { 4 };
        std::vector<int> expected_out_2_2 { 8 };
        std::vector<int> expected_out_2_3 { 12 };

        std::vector<std::vector<int>> expected_outs_2 {
            expected_out_2_1, expected_out_2_2, expected_out_2_3
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
                algo->set_input(inputs[i][j]);
                algo->exec(std::vector<sp_entity>(0));

                // check result
                auto out_res = algo->get_output();
                bool is_passed_i_j = x86_comp_output(expected_outs[i][j], out_res);
                is_passed_i &= is_passed_i_j;
                is_passed &= is_passed_i; 

                if(verbose_unit_tests_1)
                {
                    std::cout << "Evo algos - evox - genes - exec - simple "
                              << i << " - " << j << ": ";
                    passed_print(is_passed_i_j);
                } 
            }

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - evox - genes - exec - simple " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - genes - exec - simple " << " : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 

}