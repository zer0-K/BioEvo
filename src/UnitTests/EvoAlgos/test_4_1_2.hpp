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
#include "../../Models/EvoAlgos/X86Algo/FreeMolecules.hpp"

namespace ut_ea
{

    bool launch_tests_evo_algos_universe_custom_neighborhood()
    {
        bool launch_tests_evo_algos_universe_flows_custom_von_neumann(void);
        bool launch_tests_evo_algos_universe_flows_custom_read(void);
        bool launch_tests_evo_algos_universe_flows_custom_write(void);

        bool is_passed = true;

        std::cout << "Evo algos - universe - flows - custom : " << std::endl;
 
        is_passed &= launch_tests_evo_algos_universe_flows_custom_von_neumann();
        is_passed &= launch_tests_evo_algos_universe_flows_custom_read();
        is_passed &= launch_tests_evo_algos_universe_flows_custom_write();

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
     * @brief read a cell in the von neumann neighborhood
     *
     * --> tests X86
    */
    bool launch_tests_evo_algos_universe_flows_custom_read()
    {
        bool is_passed = true;

        int val = 123;
        int nb_rows = 5;
        int nb_cols = 10;

        int x_algo = 8;
        int y_algo = 3;
        int x_molecular_body = 7;
        int y_molecular_body = 2;

        //---------- ENTITIES

       
        sp_evox algo = std::make_shared<EvoX>("algo");
        algo->init();

        sp_free_molecules free_molecules = std::make_shared<FreeMolecules>("free molecules");
        free_molecules->init();

        //---------- free molecules code

        std::vector<int> molecular_body { 
            3, 2000,
            instruction::SETOS, 0, 0, 0, 1, 0, 0,
            instruction::CPYOUT, 1, 0, 0, 0, val, 0
        };

        algo->set_molecular_body(get_molecular_body_from_csv("molecular_body_base.csv")); 
        free_molecules->set_molecular_body(molecular_body);
        // set data stack at 150
        algo->set_data_at(99, 150);

        //---------- UNIVERSE

        // create the universe
        sp_univ_evo_algos_custom universe = std::make_shared<UniverseEvoXCustomNeighborhood>(nb_rows, nb_cols, "universe");
        std::vector<sp_place> places = universe->get_places();
        places[y_algo*nb_cols+x_algo]->set_entity(algo);
        places[y_molecular_body*nb_cols+x_molecular_body]->set_entity(free_molecules);

        universe->link_universe_functions_to_individuals(neighborhoodType::VON_NEUMANN, new int{ 2 });

        //  x  0 1 2 3 4 5 6 7 8 9
        //                          y    
        // 0   * * * * * * * * * *  0
        // 10  * * * * * * * * n *  1
        // 20  * * * * * * * f n n  2
        // 30  * * * * * * n n X n  3
        // 40  * * * * * * * n n n  4


        //---------- EXECUTE

        algo->set_input({ 3, 2000 });
        universe->exec();
        algo->set_input({ 5, 2000 });
        universe->exec();
        auto res = algo->get_output();
        is_passed &= x86_comp_output(res, {val});
            
        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - universe - flows - custom - read : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 

    /**
     * @brief write output in a cell in the von neumann neighborhood
     *
     * write output as free molecules in an empty cell
     *
     * --> tests X86
    */
    bool launch_tests_evo_algos_universe_flows_custom_write()
    {
        bool is_passed = true;

        int val = 123;
        int nb_rows = 5;
        int nb_cols = 10;

        int x_algo = 8;
        int y_algo = 3;
        int x_molecular_body = 7;
        int y_molecular_body = 2;

        //---------- ENTITIES

       
        sp_evox algo = std::make_shared<EvoX>("algo");
        algo->init();

        sp_free_molecules free_molecules = std::make_shared<FreeMolecules>("free molecules");
        free_molecules->init();

        //---------- free molecules code

        std::vector<int> molecular_body { 
            3, 2000,
            instruction::SETOS, 0, 0, 0, 1, 0, 0,
            instruction::CPYOUT, 1, 0, 0, 0, val, 0
        };

        algo->set_molecular_body(get_molecular_body_from_csv("molecular_body_base.csv")); 
        free_molecules->set_molecular_body(molecular_body);
        // set data stack at 150
        algo->set_data_at(99, 150);

        //---------- UNIVERSE

        // create the universe
        sp_univ_evo_algos_custom universe = std::make_shared<UniverseEvoXCustomNeighborhood>(nb_rows, nb_cols, "universe");
        std::vector<sp_place> places = universe->get_places();
        places[y_algo*nb_cols+x_algo]->set_entity(algo);
        places[y_molecular_body*nb_cols+x_molecular_body]->set_entity(free_molecules);

        universe->link_universe_functions_to_individuals(neighborhoodType::VON_NEUMANN, new int{ 2 });

        //  x  0 1 2 3 4 5 6 7 8 9
        //                          y    
        // 0   * * * * * * * * * *  0
        // 10  * * * * * * * * n *  1
        // 20  * * * * * * * f n n  2
        // 30  * * * * * * n n X n  3
        // 40  * * * * * * * n n n  4


       //---------- EXECUTE

        algo->set_input({ 3, 2000 });
        universe->exec();
        algo->set_input({ 4, 2000 });
        universe->exec();

        auto entity = universe->get_places()[3*nb_cols+9]->get_entity();

        if(entity->is_type(FREEGENES))
        {
            sp_free_molecules f = std::dynamic_pointer_cast<FreeMolecules>(entity);

            is_passed &= x86_comp_output(f->get_molecular_body(), molecular_body);
        }
        else
        {
            std::cout << "\t\tFree molecules actually not written " << std::endl;
            is_passed = false;
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - universe - flows - custom - write : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 
}