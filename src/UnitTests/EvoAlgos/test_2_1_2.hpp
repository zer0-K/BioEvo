//-------------------- EVOLUTIONARY ALGOS - X86 ALGO - BASIC - ARITHMETICS

#pragma once

#include <iostream>
#include <memory>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"

#include "../../Models/EvoAlgos/X86Algo/X86Algo.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_x86_basic_maths()
    {
        bool launch_test_evo_algos_x86_basic_INC(void);
        bool launch_test_evo_algos_x86_basic_DEC(void);
        bool launch_test_evo_algos_x86_basic_OPP(void);
        bool launch_test_evo_algos_x86_basic_ADD(void);
        bool launch_test_evo_algos_x86_basic_SUB(void);
        bool launch_test_evo_algos_x86_basic_MUL(void);
        bool launch_test_evo_algos_x86_basic_DIV(void);

        bool is_passed = true;

        std::cout << "Evo algos - x86 - basic - maths :" << std::endl;

        is_passed &= launch_test_evo_algos_x86_basic_INC(); 
        is_passed &= launch_test_evo_algos_x86_basic_DEC();
        is_passed &= launch_test_evo_algos_x86_basic_OPP();
        is_passed &= launch_test_evo_algos_x86_basic_ADD();
        is_passed &= launch_test_evo_algos_x86_basic_SUB();
        is_passed &= launch_test_evo_algos_x86_basic_MUL();
        is_passed &= launch_test_evo_algos_x86_basic_DIV();

        std::cout << "Evo algos - x86 - basic - maths : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * increment input
    */
    bool launch_test_evo_algos_x86_basic_INC()
    {
        bool is_passed = true;

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

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 0, 0, 0, input_0[2]+1, 0 };

        std::vector<std::vector<int>> expected_outs {
            expected_out_0
        };


        //---------- EXECUTE

        for(int i=0; i<codes.size(); i++)
        {
            // set phenotypic body and execute
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
    
    /**
     * decrement input
    */
    bool launch_test_evo_algos_x86_basic_DEC()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::CPYIN, 1, 1, 0, 10, 2, 0},
            { instruction::DEC, 1, 0, 0, 10, 0, 0},
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

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 0, 0, 0, input_0[2]-1, 0 };

        std::vector<std::vector<int>> expected_outs {
            expected_out_0
        };


        //---------- EXECUTE

        for(int i=0; i<codes.size(); i++)
        {
            // set phenotypic body and execute
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
                std::cout << "Evo algos - x86 - basic - maths - decrementation " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - maths - decrementation : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }    
    
    /**
     * opposite
    */
    bool launch_test_evo_algos_x86_basic_OPP()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::CPYIN, 1, 1, 0, 10, 2, 0},
            { instruction::OPP, 1, 0, 0, 10, 0, 0},
            { instruction::CPYOUT, 1, 1, 0, 3, 10, 0}
        };
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 5, 1, 0},
            { instruction::CPYIN, 1, 1, 0, 10, 2, 0},
            { instruction::OPP, 2, 0, 0, 5, 0, 0},
            { instruction::CPYOUT, 1, 1, 0, 3, 10, 0}
        };
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 0, 0, 7, 0, 0 };
        std::vector<int> input_1 { 0, 10, 7, 0, 0 };

        std::vector<std::vector<int>> inputs {
            input_0, input_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 0, 0, 0, -input_0[2], 0 };
        std::vector<int> expected_out_1 { 0, 0, 0, -input_1[2], 0 };

        std::vector<std::vector<int>> expected_outs {
            expected_out_0, expected_out_1
        };


        //---------- EXECUTE

        for(int i=0; i<codes.size(); i++)
        {
            // set phenotypic body and execute
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
                std::cout << "Evo algos - x86 - basic - maths - opposite " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - maths - opposite : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }


    /**
     * addition
    */
    bool launch_test_evo_algos_x86_basic_ADD()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::ADD, 1, 0, 0, 4, 31, 71 },
            { instruction::CPYOUT, 1, 1, 0, 3, 4, 0}
        };
        // hybride args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 10, 2, 0},
            { instruction::ADD, 1, 0, 1, 4, 71, 10},
            { instruction::CPYOUT, 1, 1, 0, 3, 4, 0}
        };
        std::vector<std::array<int,SIZE_INSTR>> code_2 { 
            { instruction::CPYIN, 1, 1, 0, 11, 3, 0},
            { instruction::ADD, 1, 1, 0, 4, 11, 31},
            { instruction::CPYOUT, 1, 1, 0, 3, 4, 0}
        };
        // reference args
        std::vector<std::array<int,SIZE_INSTR>> code_3 { 
            { instruction::CPYIN, 1, 1, 0, 10, 2, 0},
            { instruction::CPYIN, 1, 1, 0, 11, 3, 0},
            { instruction::ADD, 1, 1, 1, 4, 11, 10},
            { instruction::CPYOUT, 1, 1, 0, 3, 4, 0}
        };
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1, code_2, code_3
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 0, 0, 31, 71, 0 };
        std::vector<int> input_1 { 0, 0, 31, 0, 0 };
        std::vector<int> input_2 { 0, 0, 0, 71, 0 };
        std::vector<int> input_3 { 0, 0, 31, 71, 0 };

        std::vector<std::vector<int>> inputs {
            input_0, input_1, input_2, input_3
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 0, 0, 0, 31+71, 0 };
        std::vector<int> expected_out_1 { 0, 0, 0, input_1[2]+71, 0 };
        std::vector<int> expected_out_2 { 0, 0, 0, 31+input_2[3], 0 };
        std::vector<int> expected_out_3 { 0, 0, 0, input_3[2]+input_3[3], 0 };

        std::vector<std::vector<int>> expected_outs {
            expected_out_0, expected_out_1, expected_out_2, expected_out_3
        };


        //---------- EXECUTE

        for(int i=0; i<codes.size(); i++)
        {
            // set phenotypic body and execute
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
                std::cout << "Evo algos - x86 - basic - maths - add " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - maths - add : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * substraction
    */
    bool launch_test_evo_algos_x86_basic_SUB()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::SUB, 1, 0, 0, 4, 31, 71 },
            { instruction::CPYOUT, 1, 1, 0, 3, 4, 0}
        };
        // hybride args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 10, 2, 0},
            { instruction::SUB, 1, 0, 1, 4, 71, 10},
            { instruction::CPYOUT, 1, 1, 0, 3, 4, 0}
        };
        std::vector<std::array<int,SIZE_INSTR>> code_2 { 
            { instruction::CPYIN, 1, 1, 0, 11, 3, 0},
            { instruction::SUB, 1, 1, 0, 4, 11, 31},
            { instruction::CPYOUT, 1, 1, 0, 3, 4, 0}
        };
        // reference args
        std::vector<std::array<int,SIZE_INSTR>> code_3 { 
            { instruction::CPYIN, 1, 1, 0, 10, 2, 0},
            { instruction::CPYIN, 1, 1, 0, 11, 3, 0},
            { instruction::SUB, 1, 1, 1, 4, 11, 10},
            { instruction::CPYOUT, 1, 1, 0, 3, 4, 0}
        };
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1, code_2, code_3
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 0, 0, 31, 71, 0 };
        std::vector<int> input_1 { 0, 0, 31, 0, 0 };
        std::vector<int> input_2 { 0, 0, 31, 71, 0 };
        std::vector<int> input_3 { 0, 0, 31, 71, 0 };

        std::vector<std::vector<int>> inputs {
            input_0, input_1, input_2, input_3
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 0, 0, 0, 31-71, 0 };
        std::vector<int> expected_out_1 { 0, 0, 0, 71-input_1[2], 0 };
        std::vector<int> expected_out_2 { 0, 0, 0, input_2[3]-31, 0 };
        std::vector<int> expected_out_3 { 0, 0, 0, input_3[3]-input_3[2], 0 };

        std::vector<std::vector<int>> expected_outs {
            expected_out_0, expected_out_1, expected_out_2, expected_out_3
        };


        //---------- EXECUTE

        for(int i=0; i<codes.size(); i++)
        {
            // set phenotypic body and execute
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
                std::cout << "Evo algos - x86 - basic - maths - substract " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - maths - substract : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * multiplication
    */
    bool launch_test_evo_algos_x86_basic_MUL()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::MUL, 1, 0, 0, 4, 31, 71 },
            { instruction::CPYOUT, 1, 1, 0, 3, 4, 0}
        };
        // hybride args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 10, 2, 0},
            { instruction::MUL, 1, 0, 1, 4, 71, 10},
            { instruction::CPYOUT, 1, 1, 0, 3, 4, 0}
        };
        std::vector<std::array<int,SIZE_INSTR>> code_2 { 
            { instruction::CPYIN, 1, 1, 0, 11, 3, 0},
            { instruction::MUL, 1, 1, 0, 4, 11, 31},
            { instruction::CPYOUT, 1, 1, 0, 3, 4, 0}
        };
        // reference args
        std::vector<std::array<int,SIZE_INSTR>> code_3 { 
            { instruction::CPYIN, 1, 1, 0, 10, 2, 0},
            { instruction::CPYIN, 1, 1, 0, 11, 3, 0},
            { instruction::MUL, 1, 1, 1, 4, 11, 10},
            { instruction::CPYOUT, 1, 1, 0, 3, 4, 0}
        };
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1, code_2, code_3
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 0, 0, 31, 71, 0 };
        std::vector<int> input_1 { 0, 0, 31, 0, 0 };
        std::vector<int> input_2 { 0, 0, 0, 71, 0 };
        std::vector<int> input_3 { 0, 0, 31, 71, 0 };

        std::vector<std::vector<int>> inputs {
            input_0, input_1, input_2, input_3
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 0, 0, 0, 31*71, 0 };
        std::vector<int> expected_out_1 { 0, 0, 0, input_1[2]*71, 0 };
        std::vector<int> expected_out_2 { 0, 0, 0, 31*input_2[3], 0 };
        std::vector<int> expected_out_3 { 0, 0, 0, input_3[2]*input_3[3], 0 };

        std::vector<std::vector<int>> expected_outs {
            expected_out_0, expected_out_1, expected_out_2, expected_out_3
        };




        //---------- EXECUTE

        for(int i=0; i<codes.size(); i++)
        {
            // set phenotypic body and execute
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
                std::cout << "Evo algos - x86 - basic - maths - multiply " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - maths - multiply : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * division
    */
    bool launch_test_evo_algos_x86_basic_DIV()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::DIV, 1, 0, 0, 4, 12, 4 },
            { instruction::CPYOUT, 1, 1, 0, 3, 4, 0}
        };
        // hybride args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 10, 2, 0},
            { instruction::DIV, 1, 0, 1, 4, 12, 10},
            { instruction::CPYOUT, 1, 1, 0, 3, 4, 0}
        };
        std::vector<std::array<int,SIZE_INSTR>> code_2 { 
            { instruction::CPYIN, 1, 1, 0, 11, 3, 0},
            { instruction::DIV, 1, 1, 0, 4, 11, 4},
            { instruction::CPYOUT, 1, 1, 0, 3, 4, 0}
        };
        // reference args
        std::vector<std::array<int,SIZE_INSTR>> code_3 { 
            { instruction::CPYIN, 1, 1, 0, 10, 2, 0},
            { instruction::CPYIN, 1, 1, 0, 11, 3, 0},
            { instruction::DIV, 1, 1, 1, 4, 11, 10},
            { instruction::CPYOUT, 1, 1, 0, 3, 4, 0}
        };
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1, code_2, code_3
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 0, 0, 4, 12, 0 };
        std::vector<int> input_1 { 0, 0, 4, 0, 0 };
        std::vector<int> input_2 { 0, 0, 0, 12, 0 };
        std::vector<int> input_3 { 0, 0, 4, 12, 0 };

        std::vector<std::vector<int>> inputs {
            input_0, input_1, input_2, input_3
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 0, 0, 0, 12/4, 0 };
        std::vector<int> expected_out_1 { 0, 0, 0, 12/input_1[2], 0 };
        std::vector<int> expected_out_2 { 0, 0, 0, input_2[3]/4, 0 };
        std::vector<int> expected_out_3 { 0, 0, 0, input_3[3]/input_3[2], 0 };

        std::vector<std::vector<int>> expected_outs {
            expected_out_0, expected_out_1, expected_out_2, expected_out_3
        };


        //---------- EXECUTE

        for(int i=0; i<codes.size(); i++)
        {
            // set phenotypic body and execute
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
                std::cout << "Evo algos - x86 - basic - maths - divide " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - maths - divide : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

}