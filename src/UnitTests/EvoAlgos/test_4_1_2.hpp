//-------------------- EVOLUTIONARY ALGOS - UNIVERSE - FLOWS - CUSTOM

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../Models/EvoAlgos/Universe/CustomNeighborhoods.hpp"
#include "../../Models/EvoAlgos/Universe/UniverseEvoXCustomNeighborhood.hpp"

#include "../../Entities/EntityVoid.hpp"
#include "../../Models/EvoAlgos/X86Algo/EvoX.hpp"
#include "../../Models/EvoAlgos/X86Algo/FreeGenes.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_universe_custom_neighborhood()
    {
        bool launch_tests_evo_algos_universe_flows_custom_von_neumann(void);
        bool launch_tests_evo_algos_universe_flows_custom_read(void);
        bool launch_tests_evo_algos_universe_flows_custom_read_fail(void);
        bool launch_tests_evo_algos_universe_flows_custom_write(void);
        bool launch_tests_evo_algos_universe_flows_custom_write_fail(void);

        bool is_passed = true;

        std::cout << "Evo algos - universe - flows - custom : " << std::endl;
 
        is_passed &= launch_tests_evo_algos_universe_flows_custom_von_neumann();
        //is_passed &= launch_tests_evo_algos_universe_flows_custom_read();
        //is_passed &= launch_tests_evo_algos_universe_flows_custom_read_fail();
        //is_passed &= launch_tests_evo_algos_universe_flows_custom_write();
        //is_passed &= launch_tests_evo_algos_universe_flows_custom_write_fail();

        std::cout << "Evo algos - universe - flows - custom : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief check von neumann neighborhood
    */
    bool launch_tests_evo_algos_universe_flows_custom_von_neumann()
    {
        bool is_passed = true;

        int nb_rows = 5;
        int nb_cols = 10;
        
        int ref_x = 8;
        int ref_y = 3;
        int ref_pos = ref_y*nb_cols + ref_x;

        //  x  0 1 2 3 4 5 6 7 8 9       neighborhood numbering
        //                          y    
        // 0   * * * * * * * * * *  0        *  *  10 *  *
        // 10  * * * * * * * * n *  1        *  8  9  11 *
        // 20  * * * * * * * n n n  2        7  6  X  0  1
        // 30  * * * * * * n n X n  3        *  5  3  2  *
        // 40  * * * * * * * n n n  4        *  *  4  *  *

        // first quarter

        std::vector<int> expected_pos{
            39, -1, 49, 48, -1, 47, 37, 36, 27, 28, 18, 29
        };

        for(int i=0;i<expected_pos.size();i++)
        {
            int pos = get_pos_from_von_neumann_neighborhood(ref_pos, i, 2, nb_rows, nb_cols);
            is_passed &= pos == expected_pos[i];
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - universe - flows - custom - von neumann neighborhood : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * @brief read a universe cell
     *
     * --> tests X86
    */
    bool launch_tests_evo_algos_universe_flows_custom_read()
    {
        bool is_passed = true;

        int val1 = 123;
        int val2 = 8910;
        int val3 = 32;
        int nb_rows = 6;
        int nb_cols = 15;

        //---------- ENTITIES

       
        sp_evox algo = std::make_shared<EvoX>("algo x86");
        algo->init();

        sp_freegenes freegenes1 = std::make_shared<FreeGenes>("free genes 1");
        freegenes1->init();
        sp_freegenes freegenes2 = std::make_shared<FreeGenes>("free genes 2");
        freegenes2->init();
        sp_freegenes freegenes3 = std::make_shared<FreeGenes>("free genes 3");
        freegenes3->init();

        sp_entity_void voidentity = std::make_shared<EntityVoid>("void entity");
        voidentity->init();

        //---------- free genes code

        std::vector<int> genes1 { 
            3, 2000,
            instruction::SETOS, 0, 0, 0, 1, 0, 0,
            instruction::CPYOUT, 1, 0, 0, 0, val1, 0
        };
        std::vector<int> genes2 { 
            3, 2001,
            instruction::SETOS, 0, 0, 0, 1, 0, 0,
            instruction::CPYOUT, 1, 0, 0, 0, val2, 0
        };
        std::vector<int> genes3 { 
            3, 2002,
            instruction::SETOS, 0, 0, 0, 1, 0, 0,
            instruction::CPYOUT, 1, 0, 0, 0, val3, 0
        };


        algo->set_genes(get_genes_from_csv("genes_base.csv")); 
        freegenes1->set_genes(genes1);
        freegenes2->set_genes(genes2);
        freegenes3->set_genes(genes3);

        //---------- UNIVERSE

        // create the universe
        sp_univ_evo_algos_custom universe = std::make_shared<UniverseEvoXCustomNeighborhood>(nb_rows, nb_cols, "universe");
        std::vector<sp_place> places = universe->get_places();
        places[2*nb_cols+5]->set_entity(algo);
        places[2*nb_cols+6]->set_entity(freegenes1);
        places[3*nb_cols+5]->set_entity(freegenes2);
        places[3*nb_cols+6]->set_entity(freegenes3);

        universe->link_universe_functions_to_individuals(neighborhoodType::VON_NEUMANN, new int{ 2 });


        //---------- EXECUTE

        algo->set_input({ 3, 2000 });
        universe->exec();
        auto res = algo->get_output();
        is_passed &= x86_comp_output(res, {val1});
            
        algo->set_input({ 3, 2001 });
        universe->exec();
        res = algo->get_output();
        is_passed &= x86_comp_output(res, {val2});

        algo->set_input({ 3, 2002 });
        universe->exec();
        res = algo->get_output();
        is_passed &= !x86_comp_output(res, {val3});

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - universe - flows - custom - empty : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 

    /**
     * @brief cases for which algo can't write
     *
     * We can't read a cell containing a non free genes entity
     *
     * --> tests X86
    */
    bool launch_tests_evo_algos_universe_flows_custom_read_fail()
    {
        bool is_passed = true;

        //---------- ALGOS

        sp_x86algo algo_0 = std::make_shared<X86Algo>("first algo");
        sp_x86algo algo_1 = std::make_shared<X86Algo>("second algo");

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
            { instruction::READ, 0, 0, 0, 1, 0, 0 },
            { instruction::CPYIS, 1, 0, 0, 0, 0, 0 },
            { instruction::JRE, 0, 1, 0, 2, 0, 0 },
            { instruction::HALT, 0, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 0, 14, 0 }
        };
        // code of algo 1
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            // does nothing
            { instruction::HALT, 0, 0, 0, 0, 0, 0 }
        };

        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes { 
            code_0, code_1
        };

        // set the codes to the algos
        for(int i=0;i<algos.size();i++)
        {
           algos[i]->reset_code(codes[i]); 
        }

        //---------- inputs

        std::vector<int> input_0 { 1, 2 };
        algos[0]->set_input(input_0);

        //---------- UNIVERSE

        // 3 places
        std::vector<sp_place> places {
            std::make_shared<Place>(algos[0], 0),
            std::make_shared<Place>(algos[1], 1)
        };

        // create the universe
        sp_univ_evo_algos universe = std::make_shared<UniverseEvoAlgos>("universe", places);

        // !! most important step : links the universe methods (get_universe_size for example) to 
        // the individuals so that they can get te universe size (for example) !! 
        universe->link_universe_functions_to_individuals();


        //---------- EXPECTED OUTPUTS

        std::vector<int> expected_out { 14 };

        //---------- EXECUTE

        universe->exec();

        // free genes must have been written on the third place
        std::vector<sp_place> places_after_exec = universe->get_places();
        sp_entity first_entity = places_after_exec[0]->get_entity();
        sp_entity second_entity = places_after_exec[1]->get_entity();

        is_passed &= first_entity->is_type(X86_ALGO) 
            && second_entity->is_type(X86_ALGO);
            
        if(is_passed)
        {
            auto res = algos[0]->get_output();
            is_passed &= x86_comp_output(res, expected_out);
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - universe - flows - custom - fail read : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 

    /**
     * @brief write output in a universe cell
     *
     * write output as free genes in an empty cell
     *
     * --> tests X86
    */
    bool launch_tests_evo_algos_universe_flows_custom_write()
    {
        bool is_passed = true;

        //---------- ALGOS

        sp_x86algo algo = std::make_shared<X86Algo>("algo x86");
        algo->init();

        //---------- CODE

        std::vector<std::array<int,SIZE_INSTR>> code { 
            { instruction::SETOS, 0, 0, 0, 3, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 0, 10, 0 },
            { instruction::CPYOUT, 1, 0, 0, 1, 11, 0 },
            { instruction::CPYOUT, 1, 0, 0, 2, 12, 0 },
            { instruction::WRITE, 1, 0, 0, 0, 1, 0 },
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0 },
            { instruction::HALT, 0, 0, 0, 0, 0, 0 }
        };

        algo->reset_code(code); 

        sp_entity_void entityvoid = std::make_shared<EntityVoid>("entity void");
        entityvoid->init();

        //---------- UNIVERSE

        // 2 places : first with algo, second is empty
        std::vector<sp_place> places {
            std::make_shared<Place>(algo, 0),
            std::make_shared<Place>(entityvoid, 1)
        };

        // create the universe
        sp_univ_evo_algos universe = std::make_shared<UniverseEvoAlgos>("universe", places);

        // !! most important step : links the universe methods (get_universe_size for example) to 
        // the individuals so that they can get te universe size (for example) !! 
        universe->link_universe_functions_to_individuals();


        //---------- EXPECTED OUTPUTS

        std::vector<int> expected_out { 1, 11, 12 };
        std::vector<int> expected_genes { 10, 11, 12 };
        
        //---------- EXECUTE

        universe->exec();

        // free genes must have been written on the second place
        std::vector<sp_place> places_after_exec = universe->get_places();
        sp_entity first_entity = places_after_exec[0]->get_entity();
        sp_entity second_entity = places_after_exec[1]->get_entity();

        is_passed &= first_entity->is_type(X86_ALGO) && second_entity->is_type(FREEGENES);
            
        if(is_passed)
        {
            // if second place contains free genes, we check that they are what we expect
            sp_freegenes written_genes = std::dynamic_pointer_cast<FreeGenes>(second_entity);
            is_passed &= x86_comp_output(written_genes->get_genes(), expected_genes);

            // also compare algo out
            auto res = algo->get_output();
            is_passed &= x86_comp_output(res, expected_out);
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - universe - flows - custom - write : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 

    /**
     * @brief cases for which algo can't write
     *
     * We can't write in a non empty cell (other algo or free genes already there)
     * -> first algo write on cell 
     * -> second algo tries to write on same cell
     * -> third algo tries to write on first algo
     *
     * --> tests X86
    */
    bool launch_tests_evo_algos_universe_flows_custom_write_fail()
    {
        bool is_passed = true;

        //---------- ALGOS

        sp_x86algo algo_0 = std::make_shared<X86Algo>("first algo");
        sp_x86algo algo_1 = std::make_shared<X86Algo>("second algo");
        sp_x86algo algo_2 = std::make_shared<X86Algo>("second algo");

        std::vector<sp_x86algo> algos {
            algo_0, algo_1, algo_2
        };

        // init the algos
        for(sp_x86algo algo : algos)
        {
            algo->init();
        }

        sp_entity_void entityvoid = std::make_shared<EntityVoid>("entity void");
        entityvoid->init();

        //---------- CODES

        // code of algo 0
        std::vector<std::array<int,SIZE_INSTR>> code_0 { 
            { instruction::SETOS, 0, 0, 0, 3, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 0, 10, 0 },
            { instruction::CPYOUT, 1, 0, 0, 1, 11, 0 },
            { instruction::CPYOUT, 1, 0, 0, 2, 12, 0 },
            { instruction::WRITE, 1, 0, 0, 0, 3, 0 },
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0 },
            { instruction::HALT, 0, 0, 0, 0, 0, 0 }
        };
        // code of algo 1
        std::vector<std::array<int,SIZE_INSTR>> code_1 { 
            { instruction::SETOS, 0, 0, 0, 3, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 0, 13, 0 },
            { instruction::CPYOUT, 1, 0, 0, 1, 14, 0 },
            { instruction::CPYOUT, 1, 0, 0, 2, 15, 0 },
            { instruction::WRITE, 1, 0, 0, 0, 3, 0 },
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0 },
            { instruction::HALT, 0, 0, 0, 0, 0, 0  }
        };
        // code of algo 2
        std::vector<std::array<int,SIZE_INSTR>> code_2 { 
            { instruction::SETOS, 0, 0, 0, 3, 0, 0 },
            { instruction::CPYOUT, 1, 0, 0, 0, 16, 0 },
            { instruction::CPYOUT, 1, 0, 0, 1, 17, 0 },
            { instruction::CPYOUT, 1, 0, 0, 2, 18, 0 },
            { instruction::WRITE, 1, 0, 0, 0, 0, 0 },
            { instruction::CPYOUT, 1, 1, 0, 0, 0, 0 },
            { instruction::HALT, 0, 0, 0, 0, 0, 0 }
        };

        std::vector<std::vector<std::array<int,SIZE_INSTR>>> codes { 
            code_0, code_1, code_2
        };

        // set the codes to the algos
        for(int i=0;i<algos.size();i++)
        {
           algos[i]->reset_code(codes[i]); 
        }

        //---------- UNIVERSE

        // 3 places
        std::vector<sp_place> places {
            std::make_shared<Place>(algos[0], 0),
            std::make_shared<Place>(algos[1], 1),
            std::make_shared<Place>(algos[2], 2),
            std::make_shared<Place>(entityvoid, 3)
        };

        // create the universe
        sp_univ_evo_algos universe = std::make_shared<UniverseEvoAlgos>("universe", places);

        // !! most important step : links the universe methods (get_universe_size for example) to 
        // the individuals so that they can get te universe size (for example) !! 
        universe->link_universe_functions_to_individuals();


        //-------------------- Second round of experiment

        //---------- EXPECTED OUTPUTS

        std::vector<int> expected_out_1 { 1, 11, 12 };
        std::vector<int> expected_out_2 { 0, 14, 15 };
        std::vector<int> expected_out_3 { 0, 17, 18 };

        std::vector<std::vector<int>> expected_outs {
            expected_out_1, expected_out_2, expected_out_3
        };

        // expected freegenes value
        std::vector<int> expected_free_genes {
            10, 11, 12
        };

        //---------- EXECUTE

        universe->exec();

        // free genes must have been written on the third place
        std::vector<sp_place> places_after_exec = universe->get_places();
        sp_entity first_entity = places_after_exec[0]->get_entity();
        sp_entity second_entity = places_after_exec[1]->get_entity();
        sp_entity third_entity = places_after_exec[2]->get_entity();
        sp_entity fourth_entity = places_after_exec[3]->get_entity();

        is_passed &= first_entity->is_type(X86_ALGO) 
            && second_entity->is_type(X86_ALGO)
            && third_entity->is_type(X86_ALGO)
            && fourth_entity->is_type(FREEGENES);
            
        if(is_passed)
        {
            // we check value of free genes at fourth place
            sp_freegenes written_genes = std::dynamic_pointer_cast<FreeGenes>(fourth_entity);
            is_passed &= x86_comp_output(written_genes->get_genes(), expected_free_genes);

            // compare algos out
            for(int i=0;i<algos.size();i++)
            {
                auto res = algos[i]->get_output();
                is_passed &= x86_comp_output(res, expected_outs[i]);
            } 
        }


        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - universe - flows - custom - fail write : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 


}