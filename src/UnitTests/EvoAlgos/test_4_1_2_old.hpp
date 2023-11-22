//-------------------- EVOLUTIONARY ALGOS - UNIVERSE - FLOWS - COMPLEX

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"

#include "../../Models/EvoAlgos/X86Algo/X86Algo.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_universe_flows_complex()
    {
        bool launch_tests_evo_algos_universe_flows_complex_1(void);

        bool is_passed = true;

        std::cout << "Evo algos - universe - flows - complex :" << std::endl;
 
        //is_passed &= launch_tests_evo_algos_universe_flows_complex_1();

        std::cout << "Evo algos - universe - flows - complex : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief gene quine
    */
    bool launch_tests_evo_algos_universe_flows_complex_1()
    {
        bool is_passed = true;
        return false;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::CPYIN, 1, 1, 0, 10, 2, 0},
            { instruction::INC, 1, 0, 0, 10, 0, 0},
            { instruction::CPYOUT, 1, 1, 0, 3, 10, 0}
        };
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 0, 0, 7, 0, 0 };

        std::vector<std::vector<int>> inputs {
            input_0
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the genomes should create
        std::vector<int> expected_out_0 { 0, 0, 0, input_0[2]+1, 0 };

        std::vector<std::vector<int>> expected_outs {
            expected_out_0
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
                std::cout << "Evo algos - x86 - basic - maths - incrementation " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - maths - incrementation : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 

}