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
        bool launch_test_evo_algos_x86_basic_io_cpyus(void);
        bool launch_test_evo_algos_x86_basic_io_empty(void);
        bool launch_test_evo_algos_x86_basic_io_read(void);
        bool launch_test_evo_algos_x86_basic_io_write(void);

        bool is_passed = true;

        std::cout << "Evo algos - x86 - basic - io :" << std::endl;

        is_passed &= launch_test_evo_algos_x86_basic_io_cpyis(); 
        is_passed &= launch_test_evo_algos_x86_basic_io_setos(); 
        is_passed &= launch_test_evo_algos_x86_basic_io_cpyus(); 
        is_passed &= launch_test_evo_algos_x86_basic_io_empty(); 
        is_passed &= launch_test_evo_algos_x86_basic_io_read(); 
        is_passed &= launch_test_evo_algos_x86_basic_io_write(); 

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
     * @brief get empy universe size 
     */
    bool launch_test_evo_algos_x86_basic_io_cpyus()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::CPY, 1, 0, 0, 0, 3, 0},
            { instruction::CPYUS, 1, 0, 0, 0, 0, 0},
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0}
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

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the genomes should create
        std::vector<int> expected_out_0 { 0 };

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
                std::cout << "Evo algos - x86 - basic - io - cpyus " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - io - cpyus : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * @brief check if cell of non existing universe is empty 
     * 
     * should return false (0, i.e. cell is not empty)
     * -> means that "non existing" means full
     */
    bool launch_test_evo_algos_x86_basic_io_empty()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::CPY, 1, 0, 0, 0, 6, 0},
            { instruction::EMPTY, 1, 0, 0, 0, 4, 0},
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0}
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

        std::vector<int> expected_out_0 { 0 };

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
                std::cout << "Evo algos - x86 - basic - io - empty " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - io - empty : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * @brief read a non existing cell
     * 
     * should return an empty input 
     */
    bool launch_test_evo_algos_x86_basic_io_read()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::READ, 0, 0, 0, 4, 0, 0},
            { instruction::CPYIS, 1, 0, 0, 0, 0, 0},
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
        std::vector<int> expected_out_0 { 0 };

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
                std::cout << "Evo algos - x86 - basic - io - read " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - io - read : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * @brief write on a non existing cell
     * 
     * should return 0 (write failed) 
     */
    bool launch_test_evo_algos_x86_basic_io_write()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::CPY, 1, 0, 0, 0, 10, 0},
            { instruction::WRITE, 1, 0, 0, 0, 4, 0},
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
        std::vector<int> expected_out_0 { 0 };

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
                std::cout << "Evo algos - x86 - basic - io - write " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - io - write : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

}
