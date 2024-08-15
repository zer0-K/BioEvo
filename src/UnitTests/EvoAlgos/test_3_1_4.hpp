//-------------------- EVOLUTIONARY ALGOS - EVO X - GENES - EXEC

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"

#include "../../Models/EvoAlgos/X86Algo/EvoX.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_evox_molecular_body_exec()
    {
        bool test_evo_algos_evox_molecular_body_exec_simple(void);
        bool test_evo_algos_evox_molecular_body_exec_JMP01call(void);

        bool is_passed = true;

        std::cout << "Evo algos - evox - molecular body - exec :" << std::endl;
 
        is_passed &= test_evo_algos_evox_molecular_body_exec_simple();
        is_passed &= test_evo_algos_evox_molecular_body_exec_JMP01call();

        std::cout << "Evo algos - evox - molecular body - exec : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief exec molecular body dynamically
    */
    bool test_evo_algos_evox_molecular_body_exec_simple()
    {
        bool is_passed = true;

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();

        //---------- MOLECULAR BODY

        // molecular bodys coding simple programs
        // 
        std::vector<int> molecular_body_1 { 
            instruction::INC, 1, 0, 0, 5, 0, 0,
            instruction::EXEC, 0, 0, 0, 0, 1, 0,
            instruction::CPYOUT, 1, 1, 0, 0, 5, 0,
            instruction::HALT, 0, 0, 0, 0, 0, 0
        };
        std::vector<int> molecular_body_2 {
            instruction::XXX, 0, 0, 0, 0, 0, 0,
            instruction::INC, 1, 0, 0, 5, 0, 0,
            instruction::INC, 1, 0, 0, 5, 0, 0,
            instruction::EXEC, 0, 0, 0, 1, 2, 0,
            instruction::CPYOUT, 1, 1, 0, 0, 5, 0,
            instruction::HALT, 0, 0, 0, 0, 0, 0
        };

        std::vector<std::vector<int>> molecular_bodies {
            molecular_body_1, molecular_body_2
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

        // the expected outputs of the code the molecular bodys should create
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
                    std::cout << "Evo algos - evox - molecular body - exec - simple "
                              << i << " - " << j << ": ";
                    passed_print(is_passed_i_j);
                } 
            }

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - evox - molecular body - exec - simple " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - molecular body - exec - simple " << " : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 


    /**
     * @brief perform a function call on JMP01 architecture
    */
    bool test_evo_algos_evox_molecular_body_exec_JMP01call()
    {
        bool is_passed = true;

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();

        //---------- MOLECULAR BODY

        // molecular bodys coding simple programs

        // with automatic data stack increment
        std::vector<int> molecular_body_1 { 
            instruction::XXX, 3, 0, 0, 0, 0, 0,
            instruction::JMP, 0, 0, 0, 25, 0, 0,    // skip meta-exec func

        //----- exec fct with given id
            // args :
            //      1 - func id
            instruction::MARKER, 0, 0, 0, 0, 0, 0,
        
            // find marker with given id
            instruction::CPY, 1, 2, 1, 100, 99, 0,  // get arg 1 from stack
            instruction::CPY, 1, 0, 0, 110, -7, 0,
            instruction::ADD, 1, 1, 0, 110, 110, 7,
            instruction::GR, 1, 2, 0, 101, 110, 0,
            instruction::JRE, 0, 1, 0, 2, 101, instruction::MARKER, // marker found
            instruction::JRS, 0, 0, 0, 3, 0, 0,
            // check func id
            instruction::ADD, 1, 1, 0, 110, 110, 2,
            instruction::GR, 1, 2, 0, 101, 110, 0,
            instruction::JRE, 0, 1, 1, 3, 101, 100,
            instruction::SUB, 1, 1, 0, 110, 110, 2,
            instruction::JRS, 0, 0, 0, 8, 0, 0,

            // update data stack (args of func to exec are just before the func id)
            instruction::DEC, 1, 0, 0, 99, 0, 0,

            // set prog ptr for exec
            instruction::DIV, 1, 1, 0, 110, 110, 7,
            instruction::INC, 1, 0, 0, 0, 0, 0,
            instruction::GPTR, 2, 0, 0, 0, 0, 0,    // update prog ptr stack
            instruction::ADD, 2, 2, 0, 0, 0, 3,
            instruction::JMP, 1, 0, 0, 110, 0, 0,

            // clean the stacks
            instruction::DEC, 1, 0, 0, 0, 0, 0,     // update prog ptr stack
            instruction::CPY, 1, 2, 0, 103, 0, 0,
            instruction::DEC, 1, 0, 0, 0, 0, 0,
            instruction::JMP, 1, 0, 0, 103, 0, 0,

            instruction::MARKER, 0, 0, 0, 0, 0, 0,

        //----- main func
            instruction::MARKER, 0, 1, 0, 0, 0, 0,

            instruction::JRGE, 0, 1, 0, 3, 149, 1,      //----- l.25
            instruction::CPY, 1, 0, 0, 149, 1, 0,
            instruction::CPY, 1, 0, 0, 99, 150, 0,  // data stack begins at 150
            // clean output
            instruction::SETOS, 0, 0, 0, 2, 0, 0,
            // call muti-level exec func
            instruction::CPYIN, 1, 1, 0, 100, 0, 0,
            instruction::CALL, 0, 1, 0, 0, 100, 0,
            instruction::CPYOUT, 1, 0, 0, 1, -1234, 0,
            // end
            instruction::HALT, 0, 0, 0, 0, 0, 0,

            instruction::MARKER, 0, 1, 0, 0, 0, 0,

        //----- func 1
            instruction::MARKER, 0, 2, 0, 0, 0, 0,

            instruction::CPYOUT, 1, 0, 0, 0, 20, 0,     //----- l.35

            instruction::JMP, 2, 0, 0, 0, 0, 0,
            instruction::MARKER, 0, 2, 0, 0, 0, 0,

        //----- func 2
            instruction::MARKER, 0, 3, 0, 0, 0, 0,

            instruction::CPYOUT, 1, 0, 0, 0, 30, 0,     //----- l.39

            instruction::JMP, 2, 0, 0, 0, 0, 0,
            instruction::MARKER, 0, 3, 0, 0, 0, 0,
       };

        // without automatic data stack increment
        std::vector<int> molecular_body_2 { 
            instruction::XXX, 3, 0, 0, 0, 0, 0,
            instruction::JMP, 0, 0, 0, 25, 0, 0,    // skip meta-exec func

        //----- exec fct with given id
            // args :
            //      1 - func id
            instruction::MARKER, 0, 0, 0, 0, 0, 0,
        
            // find marker with given id
            instruction::CPY, 1, 2, 1, 100, 99, 0,  // get arg 1 from stack
            instruction::CPY, 1, 0, 0, 110, -7, 0,
            instruction::ADD, 1, 1, 0, 110, 110, 7,
            instruction::GR, 1, 2, 0, 101, 110, 0,
            instruction::JRE, 0, 1, 0, 2, 101, instruction::MARKER, // marker found
            instruction::JRS, 0, 0, 0, 3, 0, 0,
            // check func id
            instruction::ADD, 1, 1, 0, 110, 110, 2,
            instruction::GR, 1, 2, 0, 101, 110, 0,
            instruction::JRE, 0, 1, 1, 3, 101, 100,
            instruction::SUB, 1, 1, 0, 110, 110, 2,
            instruction::JRS, 0, 0, 0, 8, 0, 0,

            // update data stack (args of func to exec are just before the func id)
            instruction::DEC, 1, 0, 0, 99, 0, 0,

            // set prog ptr for exec
            instruction::DIV, 1, 1, 0, 110, 110, 7,
            instruction::INC, 1, 0, 0, 0, 0, 0,
            instruction::GPTR, 2, 0, 0, 0, 0, 0,    // update prog ptr stack
            instruction::ADD, 2, 2, 0, 0, 0, 3,
            instruction::JMP, 1, 0, 0, 110, 0, 0,

            // clean the stacks
            instruction::DEC, 1, 0, 0, 0, 0, 0,     // update prog ptr stack
            instruction::CPY, 1, 2, 0, 103, 0, 0,
            instruction::DEC, 1, 0, 0, 0, 0, 0,
            instruction::JMP, 1, 0, 0, 103, 0, 0,

            instruction::MARKER, 0, 0, 0, 0, 0, 0,

        //----- main func
            instruction::MARKER, 0, 1, 0, 0, 0, 0,

            instruction::JRGE, 0, 1, 0, 3, 149, 1,      //----- l.25
            instruction::CPY, 1, 0, 0, 149, 1, 0,
            instruction::CPY, 1, 0, 0, 99, 150, 0,  // data stack begins at 150
            // clean output
            instruction::SETOS, 0, 0, 0, 2, 0, 0,
            // call muti-level exec func
            instruction::CPYIN, 1, 1, 0, 100, 0, 0,
            instruction::INC, 1, 0, 0, 99, 0, 0,
            instruction::CALL, 0, 1, 0, 1, 100, 0,
            instruction::CPYOUT, 1, 0, 0, 1, -1234, 0,
            // end
            instruction::HALT, 0, 0, 0, 0, 0, 0,

            instruction::MARKER, 0, 1, 0, 0, 0, 0,

        //----- func 1
            instruction::MARKER, 0, 2, 0, 0, 0, 0,

            instruction::CPYOUT, 1, 0, 0, 0, 20, 0,     //----- l.36

            instruction::JMP, 2, 0, 0, 0, 0, 0,
            instruction::MARKER, 0, 2, 0, 0, 0, 0,

        //----- func 2
            instruction::MARKER, 0, 3, 0, 0, 0, 0,

            instruction::CPYOUT, 1, 0, 0, 0, 30, 0,     //----- l.40

            instruction::JMP, 2, 0, 0, 0, 0, 0,
            instruction::MARKER, 0, 3, 0, 0, 0, 0,
       };

        std::vector<std::vector<int>> molecular_bodies {
            molecular_body_1, molecular_body_2
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_1_1 { 2 };
        std::vector<int> input_1_2 { 3 };

        std::vector<std::vector<int>> inputs_1 {
            input_1_1, input_1_2
        };
        std::vector<std::vector<int>> inputs_2 = inputs_1;

        std::vector<std::vector<std::vector<int>>> inputs {
            inputs_1, inputs_2
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the molecular bodys should create
        std::vector<int> expected_out_1_1 { 20, -1234 };
        std::vector<int> expected_out_1_2 { 30, -1234 };

        std::vector<std::vector<int>> expected_outs_1 {
            expected_out_1_1, expected_out_1_2
        };

        std::vector<std::vector<int>> expected_outs_2 = expected_outs_1;

        std::vector<std::vector<std::vector<int>>> expected_outs {
            expected_outs_1, expected_outs_2 
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
                    std::cout << "Evo algos - evox - molecular body - exec - JMP01 call "
                              << i << " - " << j << ": ";
                    passed_print(is_passed_i_j);
                } 
            }

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - evox - molecular body - exec - JMP01 call " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - molecular body - exec - JMP01 call " << " : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 

}