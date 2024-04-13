#include "GeneToProgtein.hpp"

#include <fstream>

#include "../../../../Utils/Functions.hpp"
#include "../../../../Utils/Maths/RandomGen.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/FreeGenes.hpp"



GeneToProgtein::GeneToProgtein()
    :Experiment::Experiment(name_exp_bioevo_genes_evox_gtp)
{
    init();
}

void GeneToProgtein::init()
{

}

void GeneToProgtein::launch()
{
    sp_evox algo = get_base_algo();
    sp_univ_evo_algos univ = get_universe(algo);

    exec_step_1(univ, algo);
}

sp_univ_evo_algos GeneToProgtein::get_universe(sp_evox algo) 
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

sp_evox GeneToProgtein::get_base_algo()
{
    // create algo
    sp_evox algo = std::make_shared<EvoX>("evox algo");
    algo->init();

    // get genes from csv
    std::vector<int> genes = get_genes_from_csv("genes_base_algo_1.csv");
    algo->set_genes(genes);

    // set data stack at 150
    algo->set_data_at(99, 150);

    return algo;
}

std::vector<int> GeneToProgtein::get_heaviside()
{
    std::vector<int> heaviside{
        3, 1000,

        // get arg locally
        instruction::CPYIN, 1, 1, 0, 100, 2, 0,
        // if-else
        instruction::JRG, 0, 1, 0, 3, 100, 6,
        // else branch
        instruction::CPY, 1, 0, 0, 101, 0, 0,
        instruction::JRA, 0, 0, 0, 2, 0, 0,
        // if branch
        instruction::CPY, 1, 0, 0, 101, 1, 0,
        // end of if-else
        // set res in output
        instruction::SETOS, 0, 0, 0, 1, 0, 0,
        instruction::CPYOUT, 1, 1, 0, 0, 101, 0,
        // return res
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::MOV, 2, 1, 0, 99, 101, 0,
        // end of func
        instruction::JMP, 2, 0, 0, 0, 0, 0};

    return heaviside;
}

void GeneToProgtein::exec_step_1(sp_univ_evo_algos universe, sp_evox algo)
{
    //----- get Heaviside function

    std::vector<int> heaviside = get_heaviside();

    sp_freegenes freegenes = std::make_shared<FreeGenes>("free genes");
    freegenes->init();
    freegenes->set_genes(heaviside);
    universe->get_places()[1]->set_entity(freegenes);

    algo->set_input({3, 1000});
    universe->exec();


    //----- test Heaviside function

    int nb_test_inputs = 20;
    bool passed = true;
    for(int i=0;i<nb_test_inputs;i++)
    {
        int test_input = rand_gen::rand_normal(6, 4);
        int expected_output = test_input > 6 ? 1 : 0;

        algo->set_input({-1, 1000, test_input});
        universe->exec();
        auto res = algo->get_output();

        int output = res[0];
        passed = output == expected_output;
        if(!passed)
        {
            std::cout << "\tError : " << std::endl
                << "\tInput : " << test_input << std::endl
                << "\tExpected output : " << expected_output << std::endl
                << "\tGot output : " << output << std::endl;
        }
    }

    if(passed)
    {
        std::cout << "Passed ! " << std::endl;
    }
    else
    {
        std::cout << "Not passed..." << std::endl;
    }
}
