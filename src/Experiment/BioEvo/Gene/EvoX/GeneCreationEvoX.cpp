#include "GeneCreationEvoX.hpp"

#include <fstream>

#include "../../../../Utils/Functions.hpp"
#include "../../../../Utils/Maths/RandomGen.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/FreeMolecules.hpp"



GeneCreationEvoX::GeneCreationEvoX()
    :Experiment::Experiment(name_exp_bioevo_evox_gene_creation)
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
    std::string file_algo = "phenotypic_body_transcribed_iterated.csv";
    std::vector<int> phenotypic_body = get_phenotypic_body_from_csv(file_algo);
    algo->set_phenotypic_body(phenotypic_body);

    // set data stack at 150
    algo->set_data_at(99, 150);

    return algo;
}

//-------------------- step 1

void GeneCreationEvoX::exec_step_1(sp_univ_evo_algos universe, sp_evox algo)
{
    algo->set_input({5, 0, 1001});
    universe->exec();

    write_phenotypic_body_to_csv(algo->get_phenotypic_body(), "individual_new_gene_before.csv");

    for(int i=0;i<94;i++)
    {
        algo->set_input({});
        universe->exec();
    }

    // algo must have replicated at place 2
    int expected_place = 2;
    sp_entity entity = universe->get_places()[expected_place]->get_entity();
    sp_evox transcribed_algo = std::dynamic_pointer_cast<EvoX>(entity);

    if(transcribed_algo != nullptr)
    {
        std::cout << "Algo transcribed !" << std::endl;
        std::vector<int> phenotypic_body = transcribed_algo->get_phenotypic_body();
        write_phenotypic_body_to_csv(phenotypic_body, "individual_new_gene_after.csv");
    }
    else
    {
        std::cout << "Failed ! place " << expected_place
                  <<" doesn't contain an EvoX algo..." 
                  << std::endl;
    }
}
