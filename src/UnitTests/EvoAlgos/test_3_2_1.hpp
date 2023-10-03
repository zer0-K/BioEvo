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

        // genomes coding simple programs
        // 
        std::vector<int> genome_1 { 
            instruction::CPYIN, 1, 1, 0, 0, 0, 0,   // 0
            instruction::CPYIN, 1, 1, 0, 1, 1, 0,   // 1
            instruction::INC, 1, 0, 0, 2, 0, 0,     // 2 (d[2] = 1)
            instruction::ADD, 1, 1, 1, 2, 2, 2,     // 3 (d[2] = 2)
            instruction::ADD, 1, 1, 1, 2, 2, 2,     // 4 (d[2] = 4)
            instruction::CPY, 1, 1, 0, 3, 2, 0,     // 5 (d[3] = 4)
            instruction::ADD, 1, 1, 1, 2, 2, 2,     // 6 (d[2] = 8)
            instruction::CPY, 1, 1, 0, 4, 2, 0,     // 7 (d[4] = 8)
            instruction::ADD, 1, 1, 1, 2, 2, 2,     // 8 (d[2] = 16)
            instruction::ADD, 1, 1, 1, 2, 2, 3,     // 9 (d[2] = 20)
            instruction::ADD, 1, 1, 1, 2, 2, 4,     // 10 (d[2] = 28)
            instruction::INC, 1, 0, 0, 2, 0, 0,     // 11 (d[2] = 29)
            instruction::DEC, 1, 0, 0, 3, 0, 0,     // 12 (d[3] = 3)
            instruction::INC, 1, 0, 0, 6, 0, 0,     // 13 (d[6] = 1)
            instruction::INC, 1, 0, 0, 6, 0, 0,     // 14 (d[6] = 2)
            instruction::DEC, 1, 0, 0, 7, 0, 0,     // 15 (d[7] = -1)
            instruction::INC, 1, 0, 0, 7, 0, 0,     // 16 (d[7]++ (i))
            instruction::GR, 1, 1, 0, 5, 7, 0,      // 17 (d[5] = gene at i)
            instruction::JRE, 1, 1, 1, 6, 2, 5,     // 18
            instruction::JRS, 1, 1, 1, 3, 0, 0,     // 19
            instruction::ADD, 1, 1, 1, 7, 7, 4,     // 20
            instruction::DEC, 1, 0, 0, 7, 0, 0,     // 21
            instruction::DEC, 1, 0, 0, 8, 0, 0,     // 22 (j)
            instruction::SETOS, 1, 0, 0, 7, 0, 0,   // 23
            instruction::INC, 1, 0, 0, 3, 0, 0,     // 24 (d[3] = 4)
            instruction::INC, 1, 0, 0, 8, 0, 0,     // 25
            instruction::GR, 1, 1, 0, 5, 8, 0,      // 26
            instruction::CPYOUT, 1, 1, 0, 8, 5, 0,  // 27
            instruction::JRE, 1, 1, 1, 6, 7, 8,     // 28
            instruction::JRS, 1, 1, 1, 3, 0, 0,     // 29
            instruction::HALT, 0, 0, 0, 0, 0, 0     // 30
        }; 
        /*
            0-1 : dummy input (as 'template'), useless here
            2-11 : creates the number 29 (and save other numbers)
            12-15 : builds some variables for jumps (loops)
            16-19 :first loop : identify length of the genome
            20-24 : builds some vars for the next loop, and change output size
            25-29 : second loop (copying genome into output)
            30 : end
        */
        std::vector<int> genome_2 = genome_1;

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