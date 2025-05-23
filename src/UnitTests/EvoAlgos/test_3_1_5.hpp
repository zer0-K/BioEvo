//-------------------- EVOLUTIONARY ALGOS - EVO X - PHENOTYPIC BODY - EXEC

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"

#include "../../Models/EvoAlgos/X86Algo/EvoX.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_evox_phenotypic_body_regen()
    {
        bool test_evo_algos_evox_phenotypic_body_regen_simple(void);

        bool is_passed = true;

        std::cout << "Evo algos - evox - phenotypic body - regen :" << std::endl;
 
        is_passed &= test_evo_algos_evox_phenotypic_body_regen_simple();

        std::cout << "Evo algos - evox - phenotypic body - regen : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief regenerate code from phenotypic body
    */
    bool test_evo_algos_evox_phenotypic_body_regen_simple()
    {
        bool is_passed = true;

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();

        //---------- PHENOTYPIC BODY

        // phenotypic bodys coding simple programs
        // 
        std::vector<int> phenotypic_body_1 { 
            instruction::CPYIN, 1, 1, 0, 0, 0, 0,
            instruction::CPYIN, 1, 1, 0, 1, 1, 0,
            instruction::CPYIN, 1, 1, 0, 2, 2, 0,
            instruction::CPYIN, 1, 1, 0, 3, 3, 0,
            instruction::CPYIN, 1, 1, 0, 4, 4, 0,
            instruction::CPYIN, 1, 1, 0, 5, 5, 0,
            instruction::CPYIN, 1, 1, 0, 6, 6, 0,
            instruction::GCPY, 1, 1, 1, 63, 0, 6,
            instruction::REGEN, 0, 0, 0, 0, 0, 0,
            instruction::CPYOUT, 1, 1, 0, 0, 10, 0,
            instruction::HALT, 0, 0, 0, 0, 0, 0
        };

        std::vector<std::vector<int>> phenotypic_bodies {
            phenotypic_body_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_1_1 { instruction::INC, 1, 0, 0, 10, 0, 0 };

        std::vector<std::vector<int>> inputs_1 {
            input_1_1
        };

        std::vector<std::vector<std::vector<int>>> inputs {
            inputs_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_1_1 { 1 };

        std::vector<std::vector<int>> expected_outs_1 {
            expected_out_1_1
        };

        std::vector<std::vector<std::vector<int>>> expected_outs {
            expected_outs_1 
        };

        // output
        
        //---------- EXECUTE

        for(int i=0; i<expected_outs.size(); i++)
        {
            // set phenotypic body and execute
            algo->set_phenotypic_body(phenotypic_bodies[i]);
            algo->reset_data();

            // for more accurate debug in case a unit test does not pass
            bool is_passed_i = true;

            for(int j=0; j<expected_outs[i].size(); j++)
            {
                algo->set_input(inputs[i][j]);
                algo->set_output_size(expected_outs[i][j].size());
                algo->exec(std::vector<sp_entity>(0));

                // check result
                auto out_res = algo->get_output();
                bool is_passed_i_j = x86_comp_output(expected_outs[i][j], out_res);
                is_passed_i &= is_passed_i_j;
                is_passed &= is_passed_i; 

                if(verbose_unit_tests_1)
                {
                    std::cout << "Evo algos - evox - phenotypic body - regen - simple "
                              << i << " - " << j << ": ";
                    passed_print(is_passed_i_j);
                } 
            }

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - evox - phenotypic body - regen - simple " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - phenotypic body - regen - simple " << " : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 

}