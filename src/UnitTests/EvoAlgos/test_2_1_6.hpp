//-------------------- EVOLUTIONARY ALGOS - X86 ALGO - BASIC - IO

#pragma once

#include <iostream>
#include <memory>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"

#include "../../Models/EvoAlgos/X86Algo/X86Algo.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_x86_basic_io()
    {
        bool launch_test_evo_algos_x86_basic_io_cpyis(void);
        bool launch_test_evo_algos_x86_basic_io_setos(void);
        bool launch_test_evo_algos_x86_basic_io_aif(void);
        bool launch_test_evo_algos_x86_basic_io_rif(void);
        bool launch_test_evo_algos_x86_basic_io_aof(void);
        bool launch_test_evo_algos_x86_basic_io_rof(void);

        bool is_passed = true;

        std::cout << "Evo algos - x86 - basic - io :" << std::endl;

        is_passed &= launch_test_evo_algos_x86_basic_io_cpyis(); 
        is_passed &= launch_test_evo_algos_x86_basic_io_setos(); 
        is_passed &= launch_test_evo_algos_x86_basic_io_aif();
        is_passed &= launch_test_evo_algos_x86_basic_io_rif();
        is_passed &= launch_test_evo_algos_x86_basic_io_aof();
        is_passed &= launch_test_evo_algos_x86_basic_io_rof();

        std::cout << "Evo algos - x86 - basic - io : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief copy input size 
     */
    bool launch_test_evo_algos_x86_basic_io_cpyis()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::CPYIS, 1, 1, 0, 0, 0, 0},
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0}
        };
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 1000, 3, 3, 3 };

        std::vector<std::vector<int>> inputs {
            input_0
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the genomes should create
        std::vector<int> expected_out_0 { (int)input_0.size() };

        std::vector<std::vector<int>> expected_outs {
            expected_out_0
        };


        //---------- EXECUTE

        for(int i=0; i<codes.size(); i++)
        {
            // set code and execute
            algo->reset_data();
            algo->reset_code(codes[i]);

            algo->set_input(inputs[i]);
            algo->set_output_size(expected_outs[i].size());
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto out_res = algo->get_output();
            bool is_passed_i = x86_comp_output(out_res, expected_outs[i]);
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - x86 - basic - io - cpyis " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - io - cpyis : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * @brief set output size 
     */
    bool launch_test_evo_algos_x86_basic_io_setos()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0},
            { instruction::SETOS, 1, 0, 0, 0, 0, 0}
        };
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 1000 };

        std::vector<std::vector<int>> inputs {
            input_0
        };

        //---------- EXPECTED OUTPUT SIZES

        std::vector<int> expected_out_sizes {
            input_0[0]
        };


        //---------- EXECUTE

        for(int i=0; i<codes.size(); i++)
        {
            // set code and execute
            algo->reset_data();
            algo->reset_code(codes[i]);

            algo->set_input(inputs[i]);
            algo->set_output_size(0);
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto out_res = algo->get_output();
            bool is_passed_i = ((int)out_res.size() == expected_out_sizes[i]);
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - x86 - basic - io - setos " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - io - setos : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * @brief add input flow
     */
    bool launch_test_evo_algos_x86_basic_io_aif()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::AIF, 0, 0, 0, 2, -4, 0}
        };
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::AIF, 0, 0, 0, 2, -4, 0},
            { instruction::AIF, 0, 0, 0, 2, -4, 0}
        };
        std::vector<std::array<int,SIZE_INSTR>> code_2 { 
            { instruction::AIF, 0, 0, 0, 2, -4, 0},
            { instruction::AIF, 0, 0, 0, 2, -3, 0}
        };
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1, code_2
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { };
        std::vector<int> input_1 { };
        std::vector<int> input_2 { };

        std::vector<std::vector<int>> inputs {
            input_0, input_1, input_2
        };


        //---------- EXPECTED INPUT FLOWS

        std::vector<std::array<int,2>> expected_input_flows_0 {
            { 2, -4 }
        };
        std::vector<std::array<int,2>> expected_input_flows_1 {
            { 2, -4 }
        };
        std::vector<std::array<int,2>> expected_input_flows_2 {
            { 2, -4 },
            { 2, -3 }
        };

        std::vector<std::vector<std::array<int,2>>> expected_input_flows {
            expected_input_flows_0, expected_input_flows_1, expected_input_flows_2
        };

        //---------- EXECUTE

        for(int i=0; i<codes.size(); i++)
        {
            // set code and execute
            algo->reset_data();
            algo->reset_code(codes[i]);

            algo->set_input(inputs[i]);
            algo->set_output_size(0);
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto res_input_flows = algo->get_input_flows();
            bool is_passed_i = comp_flows(expected_input_flows[i],res_input_flows);
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - x86 - basic - io - aif " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - io - aif : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * @brief remove input flow
     */
    bool launch_test_evo_algos_x86_basic_io_rif()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::AIF, 0, 0, 0, 2, -4, 0},
            { instruction::AIF, 0, 0, 0, 2, -3, 0},
            { instruction::RIF, 0, 0, 0, 2, -4, 0}
        };
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { };

        std::vector<std::vector<int>> inputs {
            input_0
        };


        //---------- EXPECTED INPUT FLOWS

        std::vector<std::array<int,2>> expected_input_flows_0 {
            { 2, -3 }
        };

        std::vector<std::vector<std::array<int,2>>> expected_input_flows {
            expected_input_flows_0
        };

        //---------- EXECUTE

        for(int i=0; i<codes.size(); i++)
        {
            // set code and execute
            algo->reset_data();
            algo->reset_code(codes[i]);

            algo->set_input(inputs[i]);
            algo->set_output_size(0);
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto res_input_flows = algo->get_input_flows();
            bool is_passed_i = comp_flows(expected_input_flows[i],res_input_flows);
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - x86 - basic - io - rif " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - io - rif : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * @brief add output flow
     */
    bool launch_test_evo_algos_x86_basic_io_aof()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::AOF, 0, 0, 0, 2, -4, 0}
        };
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::AOF, 0, 0, 0, 2, -4, 0},
            { instruction::AOF, 0, 0, 0, 2, -4, 0}
        };
        std::vector<std::array<int,SIZE_INSTR>> code_2 { 
            { instruction::AOF, 0, 0, 0, 2, -4, 0},
            { instruction::AOF, 0, 0, 0, 2, -3, 0}
        };
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1, code_2
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { };
        std::vector<int> input_1 { };
        std::vector<int> input_2 { };

        std::vector<std::vector<int>> inputs {
            input_0, input_1, input_2
        };


        //---------- EXPECTED OUTPUT FLOWS

        std::vector<std::array<int,2>> expected_output_flows_0 {
            { 2, -4 }
        };
        std::vector<std::array<int,2>> expected_output_flows_1 {
            { 2, -4 }
        };
        std::vector<std::array<int,2>> expected_output_flows_2 {
            { 2, -4 },
            { 2, -3 }
        };

        std::vector<std::vector<std::array<int,2>>> expected_output_flows {
            expected_output_flows_0, expected_output_flows_1, expected_output_flows_2
        };

        //---------- EXECUTE

        for(int i=0; i<codes.size(); i++)
        {
            // set code and execute
            algo->reset_data();
            algo->reset_code(codes[i]);

            algo->set_input(inputs[i]);
            algo->set_output_size(0);
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto res_input_flows = algo->get_output_flows();
            bool is_passed_i = comp_flows(expected_output_flows[i],res_input_flows);
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - x86 - basic - io - aof " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - io - aof : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * @brief remove output flow
     */
    bool launch_test_evo_algos_x86_basic_io_rof()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::AOF, 0, 0, 0, 2, -4, 0},
            { instruction::AOF, 0, 0, 0, 2, -3, 0},
            { instruction::ROF, 0, 0, 0, 2, -4, 0}
        };
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { };

        std::vector<std::vector<int>> inputs {
            input_0
        };


        //---------- EXPECTED INPUT FLOWS

        std::vector<std::array<int,2>> expected_output_flows_0 {
            { 2, -3 }
        };

        std::vector<std::vector<std::array<int,2>>> expected_output_flows {
            expected_output_flows_0
        };

        //---------- EXECUTE

        for(int i=0; i<codes.size(); i++)
        {
            // set out and execute
            algo->reset_data();
            algo->reset_code(codes[i]);

            algo->set_input(inputs[i]);
            algo->set_output_size(0);
            algo->exec(std::vector<sp_entity>(0));

            // check result
            auto res_input_flows = algo->get_output_flows();
            bool is_passed_i = comp_flows(expected_output_flows[i],res_input_flows);
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - x86 - basic - io - rof " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - io - rof : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }
}
