//-------------------- EVOLUTIONARY ALGOS - X86 ALGO - BASIC - RANDOM

#pragma once

#include <iostream>
#include <memory>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"

#include "../../Models/EvoAlgos/X86Algo/X86Algo.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_x86_basic_random()
    {
        bool launch_test_evo_algos_x86_basic_random_normal(void);
        bool launch_test_evo_algos_x86_basic_random_unif(void);
        bool launch_test_evo_algos_x86_basic_random_geometric(void);

        bool is_passed = true;

        std::cout << "Evo algos - x86 - basic - random :" << std::endl;

        //is_passed &= launch_test_evo_algos_x86_basic_random_normal(); 
        is_passed &= launch_test_evo_algos_x86_basic_random_unif(); 
        is_passed &= launch_test_evo_algos_x86_basic_random_geometric();

        std::cout << "Evo algos - x86 - basic - random : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief normal distribution 
     * TODO : for the moment X86 Algo only has ints
    */
    bool launch_test_evo_algos_x86_basic_random_normal()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        // code
        std::vector<std::array<int,SIZE_INSTR>> code {
            { instruction::CPYIN, 0, 0, 0, 0, 0, 0},
            { instruction::CPYIN, 0, 0, 0, 1, 1, 0},
            { instruction::CPY, 0, 0, 0, 2, 0, 0},
            { instruction::RN, 0, 0, 0, 4, 4, 0},
            { instruction::ADD, 0, 0, 0, 3, 4, 0},
            { instruction::DEC, 0, 0, 0, 2, 2, 0},
            { instruction::JG, 0, 0, 0, 1, 2, 0},
            { instruction::DIV, 0, 0, 0, 3, 0, 0},
            { instruction::CPYOUT, 0, 0, 0, 0, 3, 0}
        };
        algo->set_code(code, 0);

        // input
        std::vector<int> input {
            1000, 3
        };
        algo->set_input(input);

        // output
        algo->set_output_size(1);

        // execute
        algo->exec(std::vector<sp_entity>(0));

        // check result
        auto res = algo->get_output();

        if( std::abs(res[0]) > 0.01 )
        {
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - random - normal : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief uniform distribution
    */
    bool launch_test_evo_algos_x86_basic_random_unif()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();


        //---------- CODE

        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::CPYIN, 1, 1, 0, 1, 1, 0 },
            { instruction::CPYIN, 1, 1, 0, 2, 2, 0 },
            { instruction::CPYIN, 1, 1, 0, 3, 3, 0 },
            { instruction::CPY, 1, 1, 0, 4, 0, 0 },
            { instruction::RUI, 1, 1, 1, 5, 1, 2 },
            { instruction::ADD, 1, 1, 1, 6, 6, 5 },
            { instruction::DEC, 1, 0, 0, 4, 0, 0 },
            { instruction::JG, 1, 1, 1, 3, 4, 7 },
            { instruction::DIV, 1, 1, 1, 6, 6, 0 },
            { instruction::CPYOUT, 1, 1, 0, 0, 6, 0 }
        };
 
        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes {
            code_0
        };

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input_0 { 1000, 11, 16, 5 };

        std::vector<std::vector<int>> inputs {
            input_0
        };

        //---------- EXPECTED OUTPUTS

        // the expected outputs of the code the phenotypic bodys should create
        std::vector<int> expected_out_0 { 13 };

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

            // result is 13.666 but since it's ints...
            bool is_passed_i = true;
            if( std::abs(out_res[0]-13) > 0.01 )
            {
                is_passed_i = false;
            }
            
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - x86 - basic - random - uniform " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - random - uniform : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }


    /**
     * @brief geometric distribution
    */
    bool launch_test_evo_algos_x86_basic_random_geometric()
    {
        bool is_passed = true;

        sp_x86algo algo = std::make_shared<X86Algo>("x86 algo");
        algo->init();

        int nb_loops = 50000;
        const int nb_vals_distrib = 10;

        // GEOMETRIC DISTRIB PARAMS

        std::array<int, 2> arg_rand_geom_0 { 1, 2 };
        std::array<int, 2> arg_rand_geom_1 { 3, 4 };
        std::array<int, 2> arg_rand_geom_2 { 1, 100 };

        std::vector<std::array<int, 2>> args_rand_geom {
            arg_rand_geom_0,
            arg_rand_geom_1,
            arg_rand_geom_2
        };

        //---------- CODE

        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes(args_rand_geom.size());
        for(int i=0;i<args_rand_geom.size();i++)
        {
            codes[i] = { 
                { instruction::RG, 1, 0, 0, 2, args_rand_geom[i][0], args_rand_geom[i][1] },
                { instruction::CPYOUT, 1, 1, 0, 0, 2, 0 }
            };
        }

        //---------- INPUTS

        // input (here, same for all tests for simplicity)
        std::vector<int> input { };

        //---------- EXPECTED DISTRIB

        // the expected distribution we expect
        // last vector value is the nb of outputs we get >=threshold (threshold=nb_vals_distrib-1)

        std::vector<std::array<double, nb_vals_distrib>> expected_distribs(args_rand_geom.size());

        // compute the expected distributions
        for(int i=0;i<args_rand_geom.size();i++)
        {
            std::array<double, nb_vals_distrib> expected_distrib;

            double p = ((double) args_rand_geom[i][0]) / ((double) args_rand_geom[i][1]);

            double cumul = 0;
            for(int v=0;v<nb_vals_distrib-1;v++)
            {
                double expected_prob = p;
                for(int k=0;k<v;k++)
                {
                    expected_prob *= (1-p);
                }
                cumul += expected_prob;
                expected_distrib[v] = expected_prob;
            }
            expected_distrib[nb_vals_distrib-1] = 1.0-cumul;

            expected_distribs[i] = expected_distrib;
        }


        //---------- EXECUTE

        for(int i=0; i<codes.size(); i++)
        {
            // set phenotypic body and execute
            algo->reset_data();
            algo->reset_code(codes[i]);

            algo->set_output_size(1);

            bool is_passed_i = true;
            std::array<int, nb_vals_distrib> res_distrib;
            for(int v=0;v<res_distrib.size();v++)
            {
                res_distrib[v] = 0;
            }

            // exec algo several times and check distribution
            for(int l=0;l<nb_loops;l++)
            {
                algo->exec(std::vector<sp_entity>(0));

                // check result
                auto out_res = algo->get_output();

                if(out_res[0] < 0)
                {
                    std::cout << "\t\tError : expect positive value" << std::endl;
                    is_passed_i &= false;
                    break;
                } 
                else if(out_res[0] >= nb_vals_distrib-1)
                {
                    res_distrib[nb_vals_distrib-1] += 1;
                } 
                else 
                {
                    res_distrib[out_res[0]] += 1;
                }
            }

            // compare the distribution with what we expect
            std::array<double, nb_vals_distrib> errors;
            for(int v=0;v<res_distrib.size();v++)
            {
                double res_percent = ((double) res_distrib[v]) / ((double) nb_loops);
                double expected_percent = expected_distribs[i][v];

                errors[v] = std::abs(res_percent - expected_percent)/expected_percent;
            }

            for(int v=0;v<errors.size()-1;v++)
            {
                double error_threshold = 0.1;
                if(v>8) { error_threshold = 3.0; }
                else if(v>6) { error_threshold = 3.0; }
                else if(v>4) { error_threshold = 0.5; }
                else if(v>2) { error_threshold = 0.1; }


                if(errors[v] > error_threshold)
                {
                    is_passed_i &= false;
                    break;
                }
            }
            if(errors[errors.size()-1]>10)
            {
                is_passed_i &= false;
            }
           
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - x86 - basic - random - geom " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - x86 - basic - random - geom : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }
}