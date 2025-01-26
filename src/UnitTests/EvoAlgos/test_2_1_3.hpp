//-------------------- EVOLUTIONARY ALGOS - X86 ALGO - BASIC - JUMPS

#pragma once

#include <iostream>
#include <memory>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"

#include "../../Models/EvoAlgos/X86Algo/X86Algo.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_x86_basic_jumps()
    {
        bool launch_test_evo_algos_x86_basic_CMP(void);
        bool launch_test_evo_algos_x86_basic_JMP(void);
        bool launch_test_evo_algos_x86_basic_JRA(void);
        bool launch_test_evo_algos_x86_basic_JRS(void);
        bool launch_test_evo_algos_x86_basic_JE(void);
        bool launch_test_evo_algos_x86_basic_JL(void);
        bool launch_test_evo_algos_x86_basic_JG(void);
        bool launch_test_evo_algos_x86_basic_JLE(void);
        bool launch_test_evo_algos_x86_basic_JGE(void);
        bool launch_test_evo_algos_x86_basic_JRE(void);
        bool launch_test_evo_algos_x86_basic_JRL(void);
        bool launch_test_evo_algos_x86_basic_JRG(void);
        bool launch_test_evo_algos_x86_basic_JRLE(void);
        bool launch_test_evo_algos_x86_basic_JRGE(void);

        bool is_passed = true;

        std::cout << "Evo algos - x86 - basic - jumps :" << std::endl;

        is_passed &= launch_test_evo_algos_x86_basic_CMP(); 
        is_passed &= launch_test_evo_algos_x86_basic_JMP(); 
        is_passed &= launch_test_evo_algos_x86_basic_JRA(); 
        is_passed &= launch_test_evo_algos_x86_basic_JRS(); 
        is_passed &= launch_test_evo_algos_x86_basic_JE(); 
        is_passed &= launch_test_evo_algos_x86_basic_JL(); 
        is_passed &= launch_test_evo_algos_x86_basic_JG(); 
        is_passed &= launch_test_evo_algos_x86_basic_JLE(); 
        is_passed &= launch_test_evo_algos_x86_basic_JGE(); 
        is_passed &= launch_test_evo_algos_x86_basic_JRE(); 
        is_passed &= launch_test_evo_algos_x86_basic_JRL(); 
        is_passed &= launch_test_evo_algos_x86_basic_JRG(); 
        is_passed &= launch_test_evo_algos_x86_basic_JRLE(); 
        is_passed &= launch_test_evo_algos_x86_basic_JRGE(); 

        std::cout << "Evo algos - x86 - basic - jumps : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * comparison : 0 if equal, 1 if arg1<arg2, -1 if > 
    */
    bool launch_test_evo_algos_x86_basic_CMP()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            // compare first input with itself
            { instruction::CMP, 1, 0, 0, 2, 6, 6 },
            { instruction::CPYOUT, 1, 1, 0, 0, 2, 0 },
            // compare second input with first
            { instruction::CMP, 1, 0, 0, 2, 6, 3 },
            { instruction::CPYOUT, 1, 1, 0, 1, 2, 0 },
            // compare first input with second
            { instruction::CMP, 1, 0, 0, 2, 3, 6 },
            { instruction::CPYOUT, 1, 1, 0, 2, 2, 0 }
        };
        // hybrid args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::CPYIN, 1, 1, 0, 1, 1, 0 },
            // compare first input with itself
            { instruction::CMP, 1, 1, 0, 2, 1, 6 },
            { instruction::CPYOUT, 1, 1, 0, 0, 2, 0 },
            // compare second input with first
            { instruction::CMP, 1, 1, 0, 2, 1, 3 },
            { instruction::CPYOUT, 1, 1, 0, 1, 2, 0 },
            // compare first input with second
            { instruction::CMP, 1, 1, 0, 2, 0, 6 },
            { instruction::CPYOUT, 1, 1, 0, 2, 2, 0 }
        };        
        std::vector<std::array<int,SIZE_INSTR>> code_2 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::CPYIN, 1, 1, 0, 1, 1, 0 },
            // compare first input with itself
            { instruction::CMP, 1, 0, 1, 2, 6, 1 },
            { instruction::CPYOUT, 1, 1, 0, 0, 2, 0 },
            // compare second input with first
            { instruction::CMP, 1, 0, 1, 2, 6, 0 },
            { instruction::CPYOUT, 1, 1, 0, 1, 2, 0 },
            // compare first input with second
            { instruction::CMP, 1, 0, 1, 2, 3, 1 },
            { instruction::CPYOUT, 1, 1, 0, 2, 2, 0 }
        };        
        // reference args
        std::vector<std::array<int,SIZE_INSTR>> code_3 { 
            { instruction::CPYIN, 1, 1, 1, 0, 0, 0 },
            { instruction::CPYIN, 1, 1, 0, 1, 1, 0 },
            // compare first input with itself
            { instruction::CMP, 1, 1, 1, 2, 1, 1 },
            { instruction::CPYOUT, 1, 1, 0, 0, 2, 0 },
            // compare second input with first
            { instruction::CMP, 1, 1, 1, 2, 1, 0 },
            { instruction::CPYOUT, 1, 1, 0, 1, 2, 0 },
            // compare first input with second
            { instruction::CMP, 1, 1, 1, 2, 0, 1 },
            { instruction::CPYOUT, 1, 1, 0, 2, 2, 0 }
        };
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1, code_2, code_3,
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 3, 6 };
        std::vector<int> input_1 = input_0;
        std::vector<int> input_2  = input_0;
        std::vector<int> input_3  = input_0;

        std::vector<std::vector<int>> inputs {
            input_0, input_1, input_2, input_3
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 0, -1, 1 };
        std::vector<int> expected_out_1 { 0, -1, 1 };
        std::vector<int> expected_out_2 { 0, -1, 1 };
        std::vector<int> expected_out_3 { 0, -1, 1 };

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
                std::cout << "Evo algos - x86 - basic - jumps - cmp " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - cmp : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * absolute jump
    */
    bool launch_test_evo_algos_x86_basic_JMP()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            // jump to code at line given in third arg
            { instruction::JMP, 0, 0, 0, 3, 0, 0 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 1, 1, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };
        // relative args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            // jump to code at line given in third arg
            { instruction::JMP, 1, 0, 0, 0, 0, 0 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 0, 0, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };        
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 3 };
        std::vector<int> input_1 = input_0;


        std::vector<std::vector<int>> inputs {
            input_0, input_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 1, 0 };
        std::vector<int> expected_out_1 { 1, 0 };

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
                std::cout << "Evo algos - x86 - basic - jumps - jmp " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - jmp : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * relative positive jump
    */
    bool launch_test_evo_algos_x86_basic_JRA()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            // jump to code at line given in third arg
            { instruction::JRA, 0, 0, 0, 3, 0, 0 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 1, 1, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };
        // relative args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
             // jump to code at line given in third arg
            { instruction::JRA, 1, 0, 0, 0, 0, 0 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 0, 0, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };        
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 3 };
        std::vector<int> input_1 = input_0;


        std::vector<std::vector<int>> inputs {
            input_0, input_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 1, 0 };
        std::vector<int> expected_out_1 { 1, 0 };

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
                std::cout << "Evo algos - x86 - basic - jumps - jra " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - jra : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * relative negative jump
    */
    bool launch_test_evo_algos_x86_basic_JRS()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            // jump to code at line given in third arg
            { instruction::JRS, 0, 0, 0, -3, 0, 0 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 1, 1, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };
        // relative args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
             // jump to code at line given in third arg
            { instruction::JRS, 1, 0, 0, 0, 0, 0 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 0, 0, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };        
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { -3 };
        std::vector<int> input_1 = input_0;


        std::vector<std::vector<int>> inputs {
            input_0, input_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 1, 0 };
        std::vector<int> expected_out_1 { 1, 0 };

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
                std::cout << "Evo algos - x86 - basic - jumps - jrs " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - jrs : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * conditional jump : equality (O)
    */
    bool launch_test_evo_algos_x86_basic_JE()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            // jump to code at line given in third arg
            { instruction::JE, 0, 0, 0, 7, 100, 100 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 1, 1, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };
        // relative args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::CPYIN, 1, 1, 0, 1, 1, 0 },
            { instruction::CPYIN, 1, 1, 0, 2, 2, 0 },
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
             // jump to code at line given in third arg
            { instruction::JE, 1, 1, 1, 2, 1, 0 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 0, 0, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };        
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 100, 100, 7 };
        std::vector<int> input_1 = input_0;


        std::vector<std::vector<int>> inputs {
            input_0, input_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 1, 0 };
        std::vector<int> expected_out_1 { 1, 0 };

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
                std::cout << "Evo algos - x86 - basic - jumps - je " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - je : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * jump if lower
    */
    bool launch_test_evo_algos_x86_basic_JL()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            // jump to code at line given in third arg
            { instruction::JL, 0, 0, 0, 7, 99, 100 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 1, 1, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };
        // relative args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::CPYIN, 1, 1, 0, 1, 1, 0 },
            { instruction::CPYIN, 1, 1, 0, 2, 2, 0 },
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
             // jump to code at line given in third arg
            { instruction::JL, 1, 1, 1, 2, 1, 0 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 0, 0, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };        
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 100, 99, 7 };
        std::vector<int> input_1 = input_0;


        std::vector<std::vector<int>> inputs {
            input_0, input_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 1, 0 };
        std::vector<int> expected_out_1 { 1, 0 };

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
                std::cout << "Evo algos - x86 - basic - jumps - jl " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - jl : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * jump if greater
    */
    bool launch_test_evo_algos_x86_basic_JG()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            // jump to code at line given in third arg
            { instruction::JG, 0, 0, 0, 7, 101, 100 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 1, 1, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };
        // relative args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::CPYIN, 1, 1, 0, 1, 1, 0 },
            { instruction::CPYIN, 1, 1, 0, 2, 2, 0 },
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
             // jump to code at line given in third arg
            { instruction::JG, 1, 1, 1, 2, 1, 0 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 0, 0, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };        
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 100, 101, 7 };
        std::vector<int> input_1 = input_0;


        std::vector<std::vector<int>> inputs {
            input_0, input_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 1, 0 };
        std::vector<int> expected_out_1 { 1, 0 };

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
                std::cout << "Evo algos - x86 - basic - jumps - jg " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - jg : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * jump if lower or equal
    */
    bool launch_test_evo_algos_x86_basic_JLE()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            // jump to code at line given in third arg
            { instruction::JLE, 0, 0, 0, 7, 100, 100 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 1, 1, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };
        // relative args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::CPYIN, 1, 1, 0, 1, 1, 0 },
            { instruction::CPYIN, 1, 1, 0, 2, 2, 0 },
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
             // jump to code at line given in third arg
            { instruction::JLE, 1, 1, 1, 2, 1, 0 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 0, 0, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };        
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 100, 100, 7 };
        std::vector<int> input_1 = input_0;


        std::vector<std::vector<int>> inputs {
            input_0, input_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 1, 0 };
        std::vector<int> expected_out_1 { 1, 0 };

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
                std::cout << "Evo algos - x86 - basic - jumps - jle " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - jle : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * jump if greater or equal
    */
    bool launch_test_evo_algos_x86_basic_JGE()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            // jump to code at line given in third arg
            { instruction::JGE, 0, 0, 0, 7, 100, 100 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 1, 1, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };
        // relative args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::CPYIN, 1, 1, 0, 1, 1, 0 },
            { instruction::CPYIN, 1, 1, 0, 2, 2, 0 },
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
             // jump to code at line given in third arg
            { instruction::JGE, 1, 1, 1, 2, 1, 0 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 0, 0, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };        
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 100, 100, 7 };
        std::vector<int> input_1 = input_0;


        std::vector<std::vector<int>> inputs {
            input_0, input_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 1, 0 };
        std::vector<int> expected_out_1 { 1, 0 };

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
                std::cout << "Evo algos - x86 - basic - jumps - jge " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - jge : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }
 
    /**
     * relative positive jump if equal to 0
    */
    bool launch_test_evo_algos_x86_basic_JRE()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            // jump to code at line given in third arg
            { instruction::JRE, 0, 0, 0, 3, 100, 100 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 1, 1, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };
        // relative args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::CPYIN, 1, 1, 0, 1, 1, 0 },
            { instruction::CPYIN, 1, 1, 0, 2, 2, 0 },
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
             // jump to code at line given in third arg
            { instruction::JRE, 1, 1, 1, 2, 1, 0 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 0, 0, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };        
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 100, 100, 3 };
        std::vector<int> input_1 = input_0;


        std::vector<std::vector<int>> inputs {
            input_0, input_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 1, 0 };
        std::vector<int> expected_out_1 { 1, 0 };

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
                std::cout << "Evo algos - x86 - basic - jumps - jre " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - jre : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * relative jump if lower
    */
    bool launch_test_evo_algos_x86_basic_JRL()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            // jump to code at line given in third arg
            { instruction::JRL, 0, 0, 0, 3, 99, 100 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 1, 1, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };
        // relative args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::CPYIN, 1, 1, 0, 1, 1, 0 },
            { instruction::CPYIN, 1, 1, 0, 2, 2, 0 },
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
             // jump to code at line given in third arg
            { instruction::JRL, 1, 1, 1, 2, 1, 0 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 0, 0, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };        
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 100, 99, 3 };
        std::vector<int> input_1 = input_0;


        std::vector<std::vector<int>> inputs {
            input_0, input_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 1, 0 };
        std::vector<int> expected_out_1 { 1, 0 };

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
                std::cout << "Evo algos - x86 - basic - jumps - jrl " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - jrl : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * relative jump if greater
    */
    bool launch_test_evo_algos_x86_basic_JRG()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            // jump to code at line given in third arg
            { instruction::JRG, 0, 0, 0, 3, 101, 100 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 1, 1, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };
        // relative args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::CPYIN, 1, 1, 0, 1, 1, 0 },
            { instruction::CPYIN, 1, 1, 0, 2, 2, 0 },
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
             // jump to code at line given in third arg
            { instruction::JRG, 1, 1, 1, 2, 1, 0 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 0, 0, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };        
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 100, 101, 3 };
        std::vector<int> input_1 = input_0;


        std::vector<std::vector<int>> inputs {
            input_0, input_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 1, 0 };
        std::vector<int> expected_out_1 { 1, 0 };

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
                std::cout << "Evo algos - x86 - basic - jumps - jrg " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - jrg : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }
 
    /**
     * relative jump if lower or equal
    */
    bool launch_test_evo_algos_x86_basic_JRLE()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            // jump to code at line given in third arg
            { instruction::JRLE, 0, 0, 0, 3, 100, 100 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 1, 1, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };
        // relative args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::CPYIN, 1, 1, 0, 1, 1, 0 },
            { instruction::CPYIN, 1, 1, 0, 2, 2, 0 },
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
             // jump to code at line given in third arg
            { instruction::JRLE, 1, 1, 1, 2, 1, 0 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 0, 0, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };        
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 100, 100, 3 };
        std::vector<int> input_1 = input_0;


        std::vector<std::vector<int>> inputs {
            input_0, input_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 1, 0 };
        std::vector<int> expected_out_1 { 1, 0 };

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
                std::cout << "Evo algos - x86 - basic - jumps - jrle " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - jrle : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * relative jump if greater or equal
    */
    bool launch_test_evo_algos_x86_basic_JRGE()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        // absolute args
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
            // jump to code at line given in third arg
            { instruction::JRGE, 0, 0, 0, 3, 100, 100 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 1, 1, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };
        // relative args
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::CPYIN, 1, 1, 0, 1, 1, 0 },
            { instruction::CPYIN, 1, 1, 0, 2, 2, 0 },
            { instruction::XXX, 0, 0, 0, 0, 0, 0},
             // jump to code at line given in third arg
            { instruction::JRGE, 1, 1, 1, 2, 1, 0 },
            // should be ignored
            { instruction::XXX, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 0, 0, 0 },
            // line 6
            { instruction::CPYOUT, 1, 0, 0, 0, 1, 0 }
        };        
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0, code_1
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 100, 100, 3 };
        std::vector<int> input_1 = input_0;


        std::vector<std::vector<int>> inputs {
            input_0, input_1
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 1, 0 };
        std::vector<int> expected_out_1 { 1, 0 };

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
                std::cout << "Evo algos - x86 - basic - jumps - jrge " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - jumps - jrge : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }
 
}