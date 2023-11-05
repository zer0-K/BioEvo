//-------------------- EVOLUTIONARY ALGOS - EVO X - evolution 1 - replication

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"

#include "../../Models/EvoAlgos/X86Algo/EvoX.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_evox_evolution1_replication()
    {
        bool test_evo_algos_evox_evolution1_replication_quine(void);

        bool is_passed = true;

        std::cout << "Evo algos - evox - evolution 1 - replication :" << std::endl;
 
        is_passed &= test_evo_algos_evox_evolution1_replication_quine();

        std::cout << "Evo algos - evox - evolution 1 - replication : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief gene quine
    */
    bool test_evo_algos_evox_evolution1_replication_quine()
    {
        bool is_passed = true;

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();

        //---------- GENOME

        // simple quine
        // 
        std::vector<int> genome_1 { 
            instruction::SUB, 1, 1, 0, 10, 10, 7,
            instruction::ADD, 1, 1, 0, 10, 10, 7,
            instruction::GR, 1, 2, 0, 0, 10, 0,
            instruction::JRE, 0, 0, 1, 2, instruction::HALT, 0,
            instruction::JRS, 0, 0, 0, 3, 0, 0,
            instruction::ADD, 1, 1, 0, 10, 10, 7,
            instruction::SETOS, 1, 0, 0, 10, 0, 0,
            instruction::DEC, 1, 0, 0, 11, 0, 0,
            instruction::INC, 1, 0, 0, 11, 0, 0,
            instruction::GR, 1, 2, 0, 0, 11, 0,
            instruction::CPYOUT, 2, 1, 0, 11, 0, 0,
            instruction::JRE, 0, 1, 1, 2, 10, 11,
            instruction::JRS, 0, 0, 0, 4, 0, 0,
            instruction::HALT, 0, 0, 0, 0, 0, 0
        }; 

        std::vector<std::vector<int>> genomes {
            genome_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_1_1 {
            0, 0
        };

        std::vector<std::vector<int>> inputs_1 {
            input_1_1
        };

        std::vector<std::vector<std::vector<int>>> inputs {
            inputs_1
        };

        //---------- OUTPUTS

        // output
        std::vector<int> output_1_1 = genome_1;

        std::vector<std::vector<int>> outputs_1 {
            output_1_1
        };

        std::vector<std::vector<std::vector<int>>> expected_outs {
            outputs_1
        };

       
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
                    std::cout << "Evo algos - evox - evolution 1 - replication - quine "
                              << i << " - " << j << ": ";
                    passed_print(is_passed_i_j);
                } 
            }

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - evox - evolution 1 - replication - quine " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - evolution 1 - replication - quine " << " : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 

}