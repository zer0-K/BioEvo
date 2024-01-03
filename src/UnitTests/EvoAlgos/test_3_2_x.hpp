//-------------------- EVOLUTIONARY ALGOS - EVO X - EVOLUTION PRELIMINARIES - TEST FUNCTIONS

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"

#include "../../Entities/EntityVoid.hpp"
#include "../../Models/EvoAlgos/X86Algo/FreeGenes.hpp"
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

        // check if entity is indeed free genes        
        sp_entity entity_where_freegenes = univ->get_places()[1]->get_entity();
        is_passed &= entity_where_freegenes->is_type(FREEGENES);

        if(!is_passed)
        {
            std::cout << redcol << "\tError : " << defcol
                    << "Entity at pos 1 should be free genes" << std::endl;
        }
        else
        {
            // check if free genes correspond to algo's genome
            std::vector<int> genome = algo->get_genes();
            std::vector<int> copied_genes = std::dynamic_pointer_cast<FreeGenes>(entity_where_freegenes)->get_genes();

            // copied genes don't have the teleonomical IDs at the end
            //for(int i=0;i<18;i++)
            //{
            //    copied_genes.push_back(i);
            //}
            //genome.insert(genome.begin(), genome.size());
            //genome.insert(genome.begin(), 3);
            //genome.insert(genome.begin(), 0);

            is_passed &= x86_comp_output(genome, copied_genes);
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
        // (error is rubbish, it's just to check that genome was indeed updated)

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
     * @brief acquire some free genes and putting them into genome
    */
    inline bool test_evo_algos_evox_evolution_preliminaries_behavior_simple_acquire(
        std::string test_name, sp_evox algo, sp_univ_evo_algos univ)
    {
        bool is_passed = true;

        // input that should trigger the acquire phase 
        std::vector<int> in_acquire { 3, 1000 };
        std::vector<int> in_test_acquire { 0, 0, 1000 };
        

        sp_freegenes free_genes = std::make_shared<FreeGenes>("free genes");
        free_genes->init();
        std::vector<int> genes { 3, 1000,
            instruction::SETOS, 0, 0, 0, 1, 0, 0,
            instruction::CPYOUT, 1, 0, 0, 0, -12, 0,

            instruction::JMP, 2, 0, 0, 0, 0, 0
        };
        free_genes->set_genes(genes);


        //---------- EVALUATION PHASE

        algo->set_input(in_acquire);
        univ->get_places()[1]->set_entity(free_genes);
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
     * @brief write a function as free genes in the universe
    */
    inline bool test_evo_algos_evox_evolution_preliminaries_behavior_simple_dispose(
        std::string test_name, sp_evox algo, sp_univ_evo_algos univ)
    {
        bool is_passed = true;

        // input that should trigger the function disposal phase 
        std::vector<int> in_disp { 4, 1000 };
        

        sp_entity_void entity_void = std::make_shared<EntityVoid>("entity void");
        entity_void->init();

        //----- expected free genes
        std::vector<int> expected_genes { 3, 1000,
            instruction::SETOS, 0, 0, 0, 1, 0, 0,
            instruction::CPYOUT, 1, 0, 0, 0, -12, 0,

            instruction::JMP, 2, 0, 0, 0, 0, 0
        };
        
        //---------- EVALUATION PHASE

        algo->set_input(in_disp);
        univ->get_places()[1]->set_entity(entity_void);
        univ->exec();

        // check if entity is indeed free genes        
        sp_entity entity_where_freegenes = univ->get_places()[1]->get_entity();
        is_passed &= entity_where_freegenes->is_type(FREEGENES);

        if(!is_passed)
        {
            std::cout << redcol << "\tError : " << defcol
                    << "Entity at pos 1 should be free genes" << std::endl;
        }
        else
        {
            std::vector<int> copied_genes = std::dynamic_pointer_cast<FreeGenes>(entity_where_freegenes)->get_genes();

            is_passed &= x86_comp_output(copied_genes, expected_genes);
        }



        if(verbose_unit_tests)
        {
            std::cout << "Evo algos - evox - evolution preliminaries - " << test_name << " - dispose " << " : ";
            passed_print(is_passed);
        } 

        return is_passed;
    }

}