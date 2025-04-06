#include "GeneCreationEvoX.hpp"

#include <fstream>

#include "../../../../Utils/Functions.hpp"
#include "../../../../Utils/Maths/RandomGen.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/FreeMolecules.hpp"



GeneCreationEvoX::GeneCreationEvoX()
    :Experiment::Experiment(name_exp_bioevo_phenotypic_body_evox_selfc)
{
    init();
}

void GeneCreationEvoX::init()
{
    max_nb_instr_exec = 2<<22;
}

void GeneCreationEvoX::launch()
{
    sp_evox algo = get_base_algo(1);
    sp_univ_evo_algos univ = get_universe(algo);
    exec_step_1(univ, algo);
}

sp_univ_evo_algos GeneCreationEvoX::get_universe(sp_evox algo) 
{
    int nb_entity_void = 2;

    std::vector<sp_place> places(nb_entity_void+1); 

    places[0] = std::make_shared<Place>(algo, 0);

    for(int i=0;i<nb_entity_void;i++)
    {
        sp_entity_void entity_void = std::make_shared<EntityVoid>("entity void " + std::to_string(i+1));
        entity_void->init();

        places[i+1] = std::make_shared<Place>(entity_void, i+1);
    }

    //---------- UNIVERSE

    sp_univ_evo_algos universe = std::make_shared<UniverseEvoAlgos>("universe", places);
    universe->link_universe_functions_to_individuals();

    return universe;
}

sp_evox GeneCreationEvoX::get_base_algo(int step)
{
    // create algo
    sp_evox algo = std::make_shared<EvoX>("evox algo");
    algo->init();
    algo->set_max_nb_instr_exec(max_nb_instr_exec);

    // get phenotypic body from csv
    std::string file_algo = "phenotypic_body_with_bootstrap_DNA.csv";
    std::vector<int> phenotypic_body = get_phenotypic_body_from_csv(file_algo);
    algo->set_phenotypic_body(phenotypic_body);

    // set data stack at 150
    algo->set_data_at(99, 150);

    return algo;
}

//-------------------- step 1

std::vector<int> GeneCreationEvoX::get_DNA_step_1()
{
    std::vector<int> DNA {

    };

    return DNA;
} 

void GeneCreationEvoX::exec_step_1(sp_univ_evo_algos universe, sp_evox algo)
{
    //----- get DNA as free molecules

    std::vector<int> DNA = get_DNA_step_1();

    sp_free_molecules free_molecules = std::make_shared<FreeMolecules>("free molecules");
    free_molecules->init();
    free_molecules->set_phenotypic_body(DNA);
    universe->get_places()[1]->set_entity(free_molecules);

    algo->set_input({3, -1});
    universe->exec();

    write_phenotypic_body_to_csv(algo->get_phenotypic_body(), "phenotypic_body_with_bootstrap_DNA_xxx.csv");

    // transcribe DNA only functions
    // self compilation functions
    algo->set_input({-1, 208, 114});
    universe->exec();
    algo->set_input({-1, 208, 115});
    universe->exec();
    // some remaining tRNAs
    algo->set_input({-1, 208, id_tRNA_GADD});
    universe->exec();
    // aggregators and mutators
    algo->set_input({-1, 208, 116});
    universe->exec();
    algo->set_input({-1, 208, 117});
    universe->exec();

    write_phenotypic_body_to_csv(algo->get_phenotypic_body(), "phenotypic_body_with_bootstrap_DNA_full_xxx.csv");
    // apply the self compilation functions
    algo->set_input({-1, 114});
    universe->exec();

    for(int i=0;i<88;i++)
    {
        algo->set_input({-1, 115});
        universe->exec();
    }

    algo->set_input({-1, 115});
    universe->exec();

    // algo must have replicated at place 1
    int expected_place = 1;
    sp_entity entity = universe->get_places()[expected_place]->get_entity();
    sp_evox transcribed_algo = std::dynamic_pointer_cast<EvoX>(entity);

    if(transcribed_algo != nullptr)
    {
        std::cout << "Algo transcribed !" << std::endl;
        std::vector<int> phenotypic_body = transcribed_algo->get_phenotypic_body();
        write_phenotypic_body_to_csv(phenotypic_body, "phenotypic_body_transcribed_xxx.csv");
    }
    else
    {
        std::cout << "Failed ! place " << expected_place
                  <<" doesn't contain an EvoX algo..." 
                  << std::endl;

    }

}

void GeneCreationEvoX::build_new_algo_artificially(sp_evox base_algo, std::string file_name)
{
    std::vector<int> phenotypic_body = std::vector<int>{
        0, 3, 2331, 150, -1, 0, 0,
        19, 0, 0, 0, 26, 0, 0
    };

    // add transcribed body
    auto transcribed_body = base_algo->get_output();

    phenotypic_body.insert(
        phenotypic_body.end(), 
        transcribed_body.begin(), 
        transcribed_body.end()-1
    );

    // add DNA marker
    phenotypic_body.push_back(46);
    phenotypic_body.push_back(0);
    phenotypic_body.push_back(-1);
    phenotypic_body.push_back(0);
    phenotypic_body.push_back(0);
    phenotypic_body.push_back(0);
    phenotypic_body.push_back(0);

    // add DNA
    auto DNA = get_DNA_step_1();

    phenotypic_body.insert(
        phenotypic_body.end(), 
        DNA.begin()+2, 
        DNA.end()
    );

    // add DNA marker
    phenotypic_body.push_back(46);
    phenotypic_body.push_back(0);
    phenotypic_body.push_back(-1);
    phenotypic_body.push_back(0);
    phenotypic_body.push_back(0);
    phenotypic_body.push_back(0);
    phenotypic_body.push_back(0);

    // jmp to main -> main func is at 36
    // --> to be changed in poiesis func
    phenotypic_body[11] = 36;


    write_phenotypic_body_to_csv(phenotypic_body, file_name);
}
