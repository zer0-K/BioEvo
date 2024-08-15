//-------------------- EVOLUTIONARY ALGOS - EVO X - GENES - MARKERS

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"

#include "../../Models/EvoAlgos/X86Algo/EvoX.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_evox_molecular_body_markers()
    {
        bool test_evo_algos_evox_molecular_body_marker_simple(void);

        bool is_passed = true;

        std::cout << "Evo algos - evox - molecular body - markers :" << std::endl;
 
        is_passed &= test_evo_algos_evox_molecular_body_marker_simple();

        std::cout << "Evo algos - evox - molecular body - markers : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief simple molecular marker
    */
    bool test_evo_algos_evox_molecular_body_marker_simple()
    {
        bool is_passed = true;

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();

        //---------- MOLECULAR BODY

        // molecular bodys coding simple programs
        // 
        // insert args as molecular body
        std::vector<int> molecular_body_1 { 
            
        };

        std::vector<std::vector<int>> molecular_bodies {
            molecular_body_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_1_1 {
            instruction::INC, 0, 0, 0, 7, 0, 0
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

        // the expected outputs of the code the molecular bodys should create
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
            // set molecular body and execute
            algo->set_molecular_body(molecular_bodies[i]);
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
                    std::cout << "Evo algos - evox - molecular body - markers - simple "
                              << i << " - " << j << ": ";
                    passed_print(is_passed_i_j);
                } 
            }

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - evox - molecular body - marker - simple " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - molecular body - markers - simple " << " : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 

}