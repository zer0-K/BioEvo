//-------------------- EVOLUTIONARY ALGOS - EVO X - EVOLUTION PRELIMINARIES - AUTOPOIESIS

/*

*/

#pragma once

#include <iostream>

#include "../../Utils/Functions.hpp"
#include "../../Utils/Constants.hpp"
#include "../../Models/EvoAlgos/XASMAlgo/InstructionMapping.hpp"
#include "../../Models/EvoAlgos/XASMAlgo/UtilityFunctions.hpp"
#include "../../Models/EvoAlgos/XASMAlgo/Parsing/EvoXParser.hpp"

#include "../../Entities/EntityVoid.hpp"
#include "../../Models/EvoAlgos/XASMAlgo/FreeMolecules.hpp"
#include "../../Models/EvoAlgos/XASMAlgo/EvoX.hpp"
#include "../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"

namespace ut_ea
{

    /**
     * @brief this unit test/non regression test is for simple progtreins synthesis
     */
    bool launch_tests_evo_algos_evox_evolution_preliminaries_full_replication()
    {
        bool launch_tests_evo_algos_self_replication_autopoiesis(void);
        bool launch_tests_evo_algos_self_replication_autopoiesis_evox_format(void);

        bool is_passed = true;

        std::cout << "Evo algos - evox - evolution preliminaries -  full replication : " << std::endl;
 
        is_passed &= launch_tests_evo_algos_self_replication_autopoiesis();
        is_passed &= launch_tests_evo_algos_self_replication_autopoiesis_evox_format();

        std::cout << "Evo algos - evox - evolution preliminaries -  full replication : ";
        passed_print(is_passed);

        return is_passed;
    }

    /**
     * @brief autopoietic self-replication
     *
     * An individual loaded from body_transcribed.csv triggers its own
     * self-compilation machinery and replicates itself to place 2.
     * The replicated body must be identical to the original.
     *
     * Mirrors the logic of SelfCompilationEvoX::exec_step_3.
    */
    bool launch_tests_evo_algos_self_replication_autopoiesis()
    {
        bool is_passed = true;

        //---------- ALGO

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();
        algo->set_max_nb_instr_exec(2<<22);

        std::vector<int> body = get_body_from_csv("body_transcribed.csv");
        algo->set_body(body);
        algo->set_data_at(99, 150);  // stack pointer at data[99]

        //---------- UNIVERSE

        // place 0: main algo, places 1 and 2: empty slots for replication
        std::vector<sp_place> places(3);
        places[0] = std::make_shared<Place>(algo, 0);
        for(int i = 0; i < 2; i++)
        {
            sp_entity_void entity_void = std::make_shared<EntityVoid>(
                "entity void " + std::to_string(i+1));
            entity_void->init();
            places[i+1] = std::make_shared<Place>(entity_void, i+1);
        }

        sp_univ_evo_algos universe = std::make_shared<UniverseEvoAlgos>("universe", places);
        universe->link_universe_functions_to_individuals();

        //---------- EXECUTE

        // trigger self-compilation: load function ID list from body
        algo->set_input({-1, id_self_compil_func_ID_list});
        universe->exec();

        // iterate over genes (98 genes in body_transcribed.csv)
        int nb_genes = 98;
        for(int i = 0; i < nb_genes; i++)
        {
            algo->set_input({});
            universe->exec();
        }
        algo->set_input({});
        universe->exec();

        //---------- CHECK

        // replicated individual must appear at place 2 with an identical body
        sp_entity entity = universe->get_places()[2]->get_entity();
        sp_evox transcribed_algo = std::dynamic_pointer_cast<EvoX>(entity);

        is_passed = transcribed_algo != nullptr;
        if(is_passed)
            is_passed = evox_comp_body(transcribed_algo->get_body(), body, true);

        if(verbose_unit_tests)
        {
            std::cout << "\tEvo algos - self replication - autopoiesis : ";
            passed_print(is_passed);
        }

        return is_passed;
    }

    /**
     * @brief autopoietic self-replication using a body loaded from .evox file
     *
     * Loads body_transcribed.evox via EvoXParser, runs the same self-replication
     * sequence as first test above, and verifies the replicated body is identical to
     * the evox-generated body.
     */
    bool launch_tests_evo_algos_self_replication_autopoiesis_evox_format()
    {
        bool is_passed = true;

        //---------- ALGO

        sp_evox algo = std::make_shared<EvoX>("evox algo");
        algo->init();
        algo->set_max_nb_instr_exec(2<<22);

        std::vector<int> body = EvoXParser::parse_body(project_folder + "data/body_transcribed.evox");
        algo->set_body(body);
        algo->set_data_at(99, 150);  // stack pointer at data[99]

        //---------- UNIVERSE

        std::vector<sp_place> places(3);
        places[0] = std::make_shared<Place>(algo, 0);
        for(int i = 0; i < 2; i++)
        {
            sp_entity_void entity_void = std::make_shared<EntityVoid>(
                "entity void " + std::to_string(i+1));
            entity_void->init();
            places[i+1] = std::make_shared<Place>(entity_void, i+1);
        }

        sp_univ_evo_algos universe = std::make_shared<UniverseEvoAlgos>("universe", places);
        universe->link_universe_functions_to_individuals();

        //---------- EXECUTE

        algo->set_input({-1, id_self_compil_func_ID_list});
        universe->exec();

        int nb_genes = 98;
        for(int i = 0; i < nb_genes; i++)
        {
            algo->set_input({});
            universe->exec();
        }
        algo->set_input({});
        universe->exec();

        //---------- CHECK

        sp_entity entity = universe->get_places()[2]->get_entity();
        sp_evox transcribed_algo = std::dynamic_pointer_cast<EvoX>(entity);

        is_passed = transcribed_algo != nullptr;
        if(is_passed)
            is_passed = evox_comp_body(transcribed_algo->get_body(), body, true);

        if(verbose_unit_tests)
        {
            std::cout << "\tEvo algos - self replication - autopoiesis (evox format) : ";
            passed_print(is_passed);
        }

        return is_passed;
    }


}
