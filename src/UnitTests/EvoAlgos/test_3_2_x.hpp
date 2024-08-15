//-------------------- EVOLUTIONARY ALGOS - EVO X - EVOLUTION PRELIMINARIES - TEST FUNCTIONS

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"

#include "../../Entities/EntityVoid.hpp"
#include "../../Models/EvoAlgos/X86Algo/FreeMolecules.hpp"
#include "../../Models/EvoAlgos/X86Algo/EvoX.hpp"
#include "../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"

namespace ut_ea
{
    /**
     * @brief trigger self-replication
    */
    inline bool test_evo_algos_evox_evolution_preliminaries_behavior_simple_quine(
        std::string test_name, sp_evox algo, sp_univ_evo_algos univ)
    {
        bool is_passed = true;

        // input that should trigger self-replication 

        std::vector<int> replication_trigger {
            2, 0
        };
       
        //---------- EXECUTE

        algo->set_input(replication_trigger);
        univ->exec();

        // check if entity is indeed free molecules        
        sp_entity entity_where_free_molecules = univ->get_places()[1]->get_entity();
        is_passed &= entity_where_free_molecules->is_type(FREEGENES);

        if(!is_passed)
        {
            std::cout << redcol << "\tError : " << defcol
                    << "Entity at pos 1 should be free molecules" << std::endl;
        }
        else
        {
            // check if free molecules correspond to algo's molecular body
            std::vector<int> molecular_body = algo->get_molecular_body();
            std::vector<int> copied_molecular_body = std::dynamic_pointer_cast<FreeMolecules>(entity_where_free_molecules)->get_molecular_body();

            // copied molecular molecules  don't have the teleonomical IDs at the end
            //for(int i=0;i<18;i++)
            //{
            //    copied_molecular_body.push_back(i);
            //}
            //molecular body.insert(molecular_body.begin(), molecular_body.size());
            //molecular body.insert(molecular_body.begin(), 3);
            //molecular body.insert(molecular_body.begin(), 0);

            is_passed &= x86_comp_output(molecular_body, copied_molecular_body);
        }

        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - evolution preliminaries - " << test_name << " - quine " << " : ";
            passed_print(is_passed);
        } 

        return is_passed;
    } 

    /**
     * @brief gives train data, expecting output
    */
    inline bool test_evo_algos_evox_evolution_preliminaries_behavior_simple_train_data(
        std::string test_name, sp_evox algo, sp_univ_evo_algos univ)
    {
        bool is_passed = true;

        // input that should trigger the train phase 
        // (error is rubbish, it's just to check that molecular body was indeed updated)

        std::vector<int> train_in { 0, 0, 403 };
        std::vector<int> train_error { 0, 1, 4 };
       
        //---------- EVALUATION PHASE

        algo->set_input(train_in);
        univ->exec();

        std::vector<int> res = algo->get_output();

        is_passed &= x86_comp_output(res, { -1 });

        //---------- CORRECTION PHASE

        // give back a dummy error
        algo->set_input(train_error);
        univ->exec();

        // evaluate again
        algo->set_input(train_in);
        univ->exec();

        res = algo->get_output();

        is_passed &= !x86_comp_output(res, { -1 });


        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - evolution preliminaries - " << test_name << " - train " << " : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * @brief provides test data, expecting output
    */
    inline bool test_evo_algos_evox_evolution_preliminaries_behavior_simple_test_data(
        std::string test_name, sp_evox algo, sp_univ_evo_algos univ)
    {
        bool is_passed = true;

        // input that should trigger the test phase 

        std::vector<int> test_in { 0, 0, 6 };
       
        //---------- EVALUATION PHASE

        algo->set_input(test_in);
        univ->exec();

        std::vector<int> res = algo->get_output();

        is_passed &= !x86_comp_output(res, { -1 });


        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - evolution preliminaries - " << test_name << " - test " << " : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * @brief acquire some free molecules and putting them into molecular body
    */
    inline bool test_evo_algos_evox_evolution_preliminaries_behavior_simple_acquire(
        std::string test_name, sp_evox algo, sp_univ_evo_algos univ)
    {
        bool is_passed = true;

        // input that should trigger the acquire phase 
        std::vector<int> in_acquire { 3, 1000 };
        std::vector<int> in_test_acquire { 0, 0, 1000 };
        

        sp_free_molecules free_molecules = std::make_shared<FreeMolecules>("free molecules");
        free_molecules->init();
        std::vector<int> molecular_body { 3, 1000,
            instruction::SETOS, 0, 0, 0, 1, 0, 0,
            instruction::CPYOUT, 1, 0, 0, 0, -12, 0,

            instruction::JMP, 2, 0, 0, 0, 0, 0
        };
        free_molecules->set_molecular_body(molecular_body);


        //---------- EVALUATION PHASE

        algo->set_input(in_acquire);
        univ->get_places()[1]->set_entity(free_molecules);
        univ->exec();

        algo->set_input(in_test_acquire);
        univ->exec();

        std::vector<int> res = algo->get_output();

        is_passed &= x86_comp_output(res, { -12 });


        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - evolution preliminaries - " << test_name << " - acquire " << " : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

    /**
     * @brief write a function as free molecules in the universe
    */
    inline bool test_evo_algos_evox_evolution_preliminaries_behavior_simple_dispose(
        std::string test_name, sp_evox algo, sp_univ_evo_algos univ)
    {
        bool is_passed = true;

        // input that should trigger the function disposal phase 
        std::vector<int> in_disp { 4, 1000 };
        

        sp_entity_void entity_void = std::make_shared<EntityVoid>("entity void");
        entity_void->init();

        //----- expected free molecules
        std::vector<int> expected_molecular_body { 3, 1000,
            instruction::SETOS, 0, 0, 0, 1, 0, 0,
            instruction::CPYOUT, 1, 0, 0, 0, -12, 0,

            instruction::JMP, 2, 0, 0, 0, 0, 0
        };
        
        //---------- EVALUATION PHASE

        algo->set_input(in_disp);
        univ->get_places()[1]->set_entity(entity_void);
        univ->exec();

        // check if entity is indeed free molecules        
        sp_entity entity_where_free_molecules = univ->get_places()[1]->get_entity();
        is_passed &= entity_where_free_molecules->is_type(FREEGENES);

        if(!is_passed)
        {
            std::cout << redcol << "\tError : " << defcol
                    << "Entity at pos 1 should be free molecules" << std::endl;
        }
        else
        {
            std::vector<int> copied_molecular_body = std::dynamic_pointer_cast<FreeMolecules>(entity_where_free_molecules)->get_molecular_body();

            is_passed &= x86_comp_output(copied_molecular_body, expected_molecular_body);
        }



        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - evolution preliminaries - " << test_name << " - dispose " << " : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

}