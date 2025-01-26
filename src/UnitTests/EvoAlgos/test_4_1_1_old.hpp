//-------------------- EVOLUTIONARY ALGOS - UNIVERSE - FLOWS - BASIC

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"

#include "../../Models/EvoAlgos/X86Algo/X86Algo.hpp"
#include "../../Models/EvoAlgos/X86Algo/EvoX.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_universe_flows_basic()
    {
        bool launch_tests_evo_algos_universe_flows_basic_connection(void);
        bool launch_tests_evo_algos_universe_flows_basic_disconnect_in(void);
        bool launch_tests_evo_algos_universe_flows_basic_disconnect_out(void);
        bool launch_tests_evo_algos_universe_flows_basic_fibonacci(void);

        bool is_passed = true;

        std::cout << "Evo algos - universe - flows - basic :" << std::endl;
 
        is_passed &= launch_tests_evo_algos_universe_flows_basic_connection();
        is_passed &= launch_tests_evo_algos_universe_flows_basic_disconnect_in();
        is_passed &= launch_tests_evo_algos_universe_flows_basic_disconnect_out();
        is_passed &= launch_tests_evo_algos_universe_flows_basic_fibonacci();

        std::cout << "Evo algos - universe - flows - basic : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief algo connection
     *
     * Connecting out of first algo to in of second one
     * First algo squarres the input and return it as output
     * Second algo adds 1
     * Expected out when "n" is given -> n*n+1
     *
     * --> tests X86
    */
    bool launch_tests_evo_algos_universe_flows_basic_connection()
    {
        bool is_passed = true;

        //---------- ALGOS

        sp_x86algo algo_0 = std::make_shared<X86Algo>("first flow");
        sp_x86algo algo_1 = std::make_shared<X86Algo>("second flow");

        std::vector<sp_x86algo> algos {
            algo_0, algo_1
        };

        // init the algos
        for(sp_x86algo algo : algos)
        {
            algo->init();
        }

        //---------- CODES

        // code of algo 0
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::AOF, 0, 0, 0, 0, 0, 0 },  // set connection with key-value (0;0) : OUT
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::MUL, 1, 1, 1, 0, 0, 0 },  // squarre of the copied input
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0 }
        };
        // code of algo 1
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::AIF, 0, 0, 0, 0, 0, 0 },  // set connection with key-value (0;0) : IN
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::INC, 1, 0, 0, 0, 0, 0 },  // squarre of the copied input
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0 }
        };

        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes { 
            code_0, code_1
        };

        // set the codes to the algos
        for(int i=0;i<algos.size();i++)
        {
           algos[i]->reset_code(codes[i]); 
        }

        //---------- UNIVERSE

        // create a universe with the 2 algos
        sp_univ_evo_algos universe = std::make_shared<UniverseEvoAlgos>(algos, "universe");


        //---------- EXPECTED GRAPH
        std::vector<std::array<int,2>> expected_graph {
            { 0, 1 }
        };

        //-------------------- First round of experiment

        // runs the algos with no input to init the flows
        // exec two times to generate the whole graph
        universe->exec();
        universe->exec();

        // check the io flow setup
        std::vector<std::array<int,2>> graph = universe->get_place_graph();

        is_passed &= graph.size() == expected_graph.size();
        if(is_passed)
        {
            for(int i=0;i<graph.size();i++)
            {
                is_passed &= graph[i] == expected_graph[i];
            }
        }


        //-------------------- Second round of experiment

        //---------- INPUTS

        std::vector<int> input_0 { 5 };
        std::vector<int> input_1 { 11 };
        std::vector<int> input_2 { 0 };
        std::vector<int> input_3 { 1000 };

        std::vector<std::vector<int>> inputs {
            input_0, input_1, input_2, input_3
        };

        //---------- EXPECTED OUTPUTS

        // expected out of algo 0
        std::vector<std::vector<int>> expected_out_0 {
            { 25 },
            { 121 },
            { 0 },
            { 1000000 }
        };

        // expected out of algo 1
        std::vector<std::vector<int>> expected_out_1 {
            { 26 },
            { 122 },
            { 1 },
            { 1000001 }
        };

        std::vector<std::vector<std::vector<int>>> expected_outs {
            expected_out_0, expected_out_1
        };


        //---------- EXECUTE

        for(int i=0; i<inputs.size(); i++)
        {
            // set the input of the first algo
            algo_0->set_input(inputs[i]);

            // execute
            universe->exec();
            
            // check results
            auto out_0 = algo_0->get_output();
            auto out_1 = algo_1->get_output();

            bool is_passed_i = x86_comp_output(expected_outs[0][i], out_0);
            is_passed_i &= x86_comp_output(expected_outs[1][i], out_1);
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - universe - flows - basic - connection " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - universe - flows - basic - connection : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 

    /**
     * @brief algo disconnection : remove input flow
     *
     * Connecting out of first algo to in of second one and then disconnecting second in flow
     *
     * --> tests X86
    */
    bool launch_tests_evo_algos_universe_flows_basic_disconnect_in()
    {
        bool is_passed = true;

        //---------- ALGOS

        sp_x86algo algo_0 = std::make_shared<X86Algo>("first flow");
        sp_x86algo algo_1 = std::make_shared<X86Algo>("second flow");

        std::vector<sp_x86algo> algos {
            algo_0, algo_1
        };

        // init the algos
        for(sp_x86algo algo : algos)
        {
            algo->init();
        }

        //---------- CODES

        // code of algo 0
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::AOF, 0, 0, 0, 0, 0, 0 },  // set connection with key-value (0;0) : OUT
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::MUL, 1, 1, 1, 0, 0, 0 },  // squarre of the copied input
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0 }
        };
        // codes of algo 1 :
        // connection
        std::vector<std::array<int,SIZE_INSTR>> code_1_connect { 
            { instruction::AIF, 0, 0, 0, 0, 0, 0 },  // set connection with key-value (0;0) : IN
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::INC, 1, 0, 0, 0, 0, 0 },  // squarre of the copied input
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0 }
        };
        // disconnection
        std::vector<std::array<int,SIZE_INSTR>> code_1_disconnect { 
            { instruction::RIF, 0, 0, 0, 0, 0, 0 },  // remove connection
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::INC, 1, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0 }
        };

        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes { 
            code_0, code_1_connect
        };

        // set the codes to the algos
        for(int i=0;i<algos.size();i++)
        {
           algos[i]->reset_code(codes[i]); 
        }

        //---------- UNIVERSE

        // create a universe with the 2 algos
        sp_univ_evo_algos universe = std::make_shared<UniverseEvoAlgos>(algos, "universe");


        //---------- EXPECTED GRAPH
        std::vector<std::array<int,2>> expected_graph {
            { 0, 1 }
        };

        //-------------------- First round of experiment

        // runs the algos with no input to init the flows
        // exec two times to generate the whole graph
        universe->exec();
        universe->exec();

        // check the io flow setup
        std::vector<std::array<int,2>> graph = universe->get_place_graph();

        is_passed &= graph.size() == expected_graph.size();
        if(is_passed)
        {
            for(int i=0;i<graph.size();i++)
            {
                is_passed &= graph[i] == expected_graph[i];
            }
        }


        //-------------------- Second round of experiment

        //---------- INPUTS

        std::vector<int> input_0 { 5 };
        std::vector<int> input_1 { 11 };
        std::vector<int> input_2 { 7 };
        std::vector<int> input_3 { 1 };
        std::vector<int> input_4 { 1000 };

        std::vector<std::vector<int>> inputs {
            input_0, input_1, input_2, input_3, input_4
        };

        //---------- EXPECTED OUTPUTS

        // expected out of algo 0
        std::vector<std::vector<int>> expected_out_0 {
            { 25 },
            { 121 },
            { 49 },
            { 1 },
            { 1000000 }
        };

        // expected out of algo 1
        std::vector<std::vector<int>> expected_out_1 {
            { 26 },
            { 122 },
            { 50 },
            { 51 },
            { 52 }
        };

        std::vector<std::vector<std::vector<int>>> expected_outs {
            expected_out_0, expected_out_1
        };


        //---------- EXECUTE

        for(int i=0; i<inputs.size(); i++)
        {
            // set the input of the first algo
            algo_0->set_input(inputs[i]);

            // disconnect at 3rd step
            if(i==2)
            {
                algo_1->reset_code(code_1_disconnect);
                codes[1] = code_1_disconnect;
                // ! data of algo_1 is the same
            }

            // execute
            universe->exec();
            
            // check results
            auto out_0 = algo_0->get_output();
            auto out_1 = algo_1->get_output();

            bool is_passed_i = x86_comp_output(expected_outs[0][i], out_0);
            is_passed_i &= x86_comp_output(expected_outs[1][i], out_1);
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - universe - flows - basic - disconnect - in " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - universe - flows - basic - disconnect - in : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 

    /**
     * @brief algo disconnection : remove output flow
     *
     * Connecting out of first algo to in of second one and then disconnecting first out flow
     *
     * --> tests X86
    */
    bool launch_tests_evo_algos_universe_flows_basic_disconnect_out()
    {
        bool is_passed = true;

        //---------- ALGOS

        sp_x86algo algo_0 = std::make_shared<X86Algo>("first flow");
        sp_x86algo algo_1 = std::make_shared<X86Algo>("second flow");

        std::vector<sp_x86algo> algos {
            algo_0, algo_1
        };

        // init the algos
        for(sp_x86algo algo : algos)
        {
            algo->init();
        }

        //---------- CODES

        // code of algo 0 :
        // connect
        std::vector<std::array<int,SIZE_INSTR>> code_0_connect { 
            { instruction::AOF, 0, 0, 0, 0, 0, 0 },  // set connection with key-value (0;0) : OUT
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::MUL, 1, 1, 1, 0, 0, 0 },  // squarre of the copied input
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0 }
        };
        // disconnect
         std::vector<std::array<int,SIZE_INSTR>> code_0_disconnect { 
            { instruction::ROF, 0, 0, 0, 0, 0, 0 },  // remove connection with key-value (0;0) : OUT
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::MUL, 1, 1, 1, 0, 0, 0 },  // squarre of the copied input
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0 }
        };
        // codes of algo 1
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::AIF, 0, 0, 0, 0, 0, 0 },  // set connection with key-value (0;0) : IN
            { instruction::CPYIN, 1, 1, 0, 0, 0, 0 },
            { instruction::INC, 1, 0, 0, 0, 0, 0 },  // squarre of the copied input
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0 }
        };

        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes { 
            code_0_connect, code_1
        };

        // set the codes to the algos
        for(int i=0;i<algos.size();i++)
        {
           algos[i]->reset_code(codes[i]); 
        }

        //---------- UNIVERSE

        // create a universe with the 2 algos
        sp_univ_evo_algos universe = std::make_shared<UniverseEvoAlgos>(algos, "universe");


        //---------- EXPECTED GRAPH
        std::vector<std::array<int,2>> expected_graph {
            { 0, 1 }
        };

        //-------------------- First round of experiment

        // runs the algos with no input to init the flows
        // exec two times to generate the whole graph
        universe->exec();
        universe->exec();

        // check the io flow setup
        std::vector<std::array<int,2>> graph = universe->get_place_graph();

        is_passed &= graph.size() == expected_graph.size();
        if(is_passed)
        {
            for(int i=0;i<graph.size();i++)
            {
                is_passed &= graph[i] == expected_graph[i];
            }
        }


        //-------------------- Second round of experiment

        //---------- INPUTS

        std::vector<int> input_0 { 5 };
        std::vector<int> input_1 { 11 };
        std::vector<int> input_2 { 7 };
        std::vector<int> input_3 { 1 };
        std::vector<int> input_4 { 1000 };

        std::vector<std::vector<int>> inputs {
            input_0, input_1, input_2, input_3, input_4
        };

        //---------- EXPECTED OUTPUTS

        // expected out of algo 0
        std::vector<std::vector<int>> expected_out_0 {
            { 25 },
            { 121 },
            { 49 },
            { 1 },
            { 1000000 }
        };

        // expected out of algo 1
        std::vector<std::vector<int>> expected_out_1 {
            { 26 },
            { 122 },
            { 123 },
            { 124 },
            { 125 }
        };

        std::vector<std::vector<std::vector<int>>> expected_outs {
            expected_out_0, expected_out_1
        };


        //---------- EXECUTE

        for(int i=0; i<inputs.size(); i++)
        {
            // set the input of the first algo
            algo_0->set_input(inputs[i]);

            // disconnect at 3rd step
            if(i==2)
            {
                algo_0->reset_code(code_0_disconnect);
                codes[0] = code_0_disconnect;
                // ! data of algo_0 is the same
            }

            // execute
            universe->exec();
            
            // check results
            auto out_0 = algo_0->get_output();
            auto out_1 = algo_1->get_output();

            bool is_passed_i = x86_comp_output(expected_outs[0][i], out_0);
            is_passed_i &= x86_comp_output(expected_outs[1][i], out_1);
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - universe - flows - basic - disconnect - out " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - universe - flows - basic - disconnect - out : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 

    /**
     * @brief algo connection : Fibonacci
     *
     * Fibonacci using the two-algo connection
     * ! no input set : initial state is in data !
     *
     * --> tests evoX
     */
    bool launch_tests_evo_algos_universe_flows_basic_fibonacci()
    {
        bool is_passed = true;

        //---------- ALGOS

        sp_evox algo_0 = std::make_shared<EvoX>("first flow");
        sp_evox algo_1 = std::make_shared<EvoX>("second flow");

        std::vector<sp_evox> algos {
            algo_0, algo_1
        };

        // init the algos
        for(sp_evox algo : algos)
        {
            algo->init();
        }

        //---------- GENES

        // phenotypic body of algo 0
        std::vector<int> phenotypic_body_0 { 
            instruction::AIF, 0, 0, 0, 0, 0, 0,  // to connect in to second algo out
            instruction::AOF, 0, 0, 0, 1, 0, 0,  // to connect out to second algo in
            instruction::CPYIN, 1, 1, 0, 1, 0, 0,
            instruction::ADD, 1, 1, 1, 0, 0, 1,  // fibo
            instruction::CPYOUT, 1, 1, 0, 0, 0, 0
        };
        // phenotypic body of algo 1
        std::vector<int> phenotypic_body_1 { 
            instruction::AIF, 0, 0, 0, 1, 0, 0,  // to connect in to first algo out
            instruction::AOF, 0, 0, 0, 0, 0, 0,  // to connect out to first algo in
            instruction::CPYIN, 1, 1, 0, 1, 0, 0,
            instruction::ADD, 1, 1, 1, 0, 0, 1,  // squarre of the copied input
            instruction::CPYOUT, 1, 1, 0, 0, 0, 0
        };

        std::vector<std::vector<int>> phenotypic_body {
            phenotypic_body_0, phenotypic_body_1
        };

        // set the phenotypic body to the algos
        for(int i=0;i<algos.size();i++)
        {
           algos[i]->set_phenotypic_body(phenotypic_body[i]); 
        }

        //---------- UNIVERSE

        // create a universe with the 2 algos
        sp_univ_evo_algos universe = std::make_shared<UniverseEvoAlgos>(algos, "universe");


        //-------------------- Exec

        // void exec to create the stream graph
        universe->exec();
        universe->exec();


        //---------- "INPUT"
        
        // no input, change the data init state instead
        algo_1->set_data_at(0,1);


        //---------- EXPECTED OUTPUTS

        // expected out of algo 0
        std::vector<std::vector<int>> expected_out_0 {
            { 0 },
            { 1 },
            { 3 },
            { 8 },
            { 21 }
        };

        // expected out of algo 1
        std::vector<std::vector<int>> expected_out_1 {
            { 1 },
            { 2 },
            { 5 },
            { 13 },
            { 34 }
        };

        std::vector<std::vector<std::vector<int>>> expected_outs {
            expected_out_0, expected_out_1
        };


        //---------- EXECUTE

        for(int i=0; i<expected_out_0.size(); i++)
        {
            // execute
            universe->exec();
            
            // check results
            auto out_0 = algo_0->get_output();
            auto out_1 = algo_1->get_output();

            bool is_passed_i = x86_comp_output(expected_outs[0][i], out_0);
            is_passed_i &= x86_comp_output(expected_outs[1][i], out_1);
            is_passed &= is_passed_i; 

            if(verbose_unit_tests_1)
            {
                std::cout << "Evo algos - universe - flows - basic - fibonacci " << i << " : ";
                passed_print(is_passed_i);
            } 
       }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - universe - flows - basic - fibonacci : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }
}