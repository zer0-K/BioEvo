#include "SelfCompilationEvoX.hpp"

#include <fstream>

#include "../../../../../Utils/Functions.hpp"
#include "../../../../../Utils/Maths/RandomGen.hpp"
#include "../../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../../../../Models/EvoAlgos/X86Algo/FreeGenes.hpp"



SelfCompilationEvoX::SelfCompilationEvoX()
    :Experiment::Experiment(name_exp_bioevo_genes_evox_selfc)
{
    init();
}

void SelfCompilationEvoX::init()
{
}

void SelfCompilationEvoX::launch()
{
    sp_evox algo = get_base_algo();
    sp_univ_evo_algos univ = get_universe(algo);

    exec_step_1(univ, algo);
}

sp_univ_evo_algos SelfCompilationEvoX::get_universe(sp_evox algo) 
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

sp_evox SelfCompilationEvoX::get_base_algo()
{
    // create algo
    sp_evox algo = std::make_shared<EvoX>("evox algo");
    algo->init();

    // get genes from csv
    std::vector<int> genes = get_genes_from_csv("genes_with_ribosome_and_built_heaviside.csv");
    algo->set_genes(genes);

    // set data stack at 150
    algo->set_data_at(99, 150);

    return algo;
}

//-------------------- step 1

std::vector<int> SelfCompilationEvoX::get_DNA_step_1()
{
    int LV_place = 1000;

    std::vector<int> DNA {
        3, -1,

        // 0 - func executor

        GSTART_ID, 0, id_tRNA_CVARS, LV_place, 5, id_tRNA_IVARS,id_tRNA_GTSLVD,
        1, id_tRNA_SLVcst, 2, 0, id_tRNA_SLVcst, 3, 1,
        // while loop
        id_tRNA_IF0, 3, id_tRNA_OPELVcst, 0, 2, 7, id_tRNA_RGLVLV,
        4, 2, id_tRNA_CMPLVcst, 0, 4, instruction::MARKER, 3,
        id_tRNA_IF0, 3, id_tRNA_OPELVcst, 0, 2, 2, id_tRNA_RGLVLV,
        4, 2, id_tRNA_CMPLVLV, 0, 4, 1, id_tRNA_OPELVcst,
        1, 3, 1, id_tRNA_IF0, 3, id_tRNA_SIJ, id_tRNA_OPELVcst,
        2, 2, id_tRNA_SEJ, id_tRNA_SIJ, id_tRNA_SLVcst, 3, 1,
        id_tRNA_SEJ, id_tRNA_PLVSWI, id_tRNA_OPELVcst, 3, 2, 7, id_tRNA_INCcst,
        0, 0, id_tRNA_SP_GPTR, id_tRNA_SP_FCTADD, id_tRNA_JLV, 2, id_tRNA_INCcst, 1, 0,
        id_tRNA_SP_GFPTRLV, 5, id_tRNA_INCcst, 1, 0, id_tRNA_JLV, 5, 
        GSTOP_ID, 0, 0, 0, 0, 0, 0,


        // 1 - main func

        GSTART_ID, 1, id_tRNA_CVARS, LV_place, 0, id_tRNA_IVARS, id_tRNA_CALLcst,
        2, id_tRNA_HALT, id_tRNA_RET, GSTOP_ID, 0, 0, 0,


        // 103 - search and pick free genes

        GSTART_ID, 103, id_tRNA_CVARS, LV_place, 1, id_tRNA_IVARS, id_tRNA_CALLcst,
        300, id_tRNA_GTSLVD, 1, id_tRNA_IF0, 1, id_tRNA_CALLcst, 201,
        id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_RET, GSTOP_ID, 0, 0, 0,


        // 200 - calc genome size

        GSTART_ID, 200, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_SLVcst,
        1, 1, id_tRNA_SLVcst, 2, -7, id_tRNA_IF0, 1,
        id_tRNA_OPELVcst, 0, 2, 7, id_tRNA_RGLVLV, 3, 2,
        id_tRNA_CMPLVcst, 0, 3, instruction::MARKER, 1, id_tRNA_IF0, 1,
        id_tRNA_INCLV, 0, 2, id_tRNA_RGLVLV, 3, 2, id_tRNA_INCLV,
        1, 2, id_tRNA_CMPLVcst, 0, 2, -1, id_tRNA_SIJ,
        id_tRNA_SEJ, id_tRNA_OPELVcst, 1, 1, 1, id_tRNA_SWJ, id_tRNA_OPELVcst,
        0, 2, 7, id_tRNA_GScstLV, 2, 2, id_tRNA_RET,
        GSTOP_ID, 0, 0, 0, 0, 0, 0,


        // 201 - copy free genes into code as new func

        GSTART_ID, 201, id_tRNA_CVARS, LV_place, 9, id_tRNA_IVARS, id_tRNA_SLVcst,
        8, 1, id_tRNA_SLVcst, 6, 0, id_tRNA_IF0, 8, 
        id_tRNA_RGLVLV, 1, 6, id_tRNA_CMPLVcst, 0, 1, instruction::MARKER,
        7, id_tRNA_IF0, 7, id_tRNA_INCcst, 0, 6, id_tRNA_RGLVLV, 
        1, 6, id_tRNA_INCcst, 1, 6, id_tRNA_CMPLVcst, 0, 
        1, -1, 7, id_tRNA_IF0, 7, id_tRNA_SLVcst, 8, 
        0, id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_OPELVcst, 0, 
        6, 8, id_tRNA_SWJ, id_tRNA_GILV, 1, 1, id_tRNA_SLVcst, 
        2, 1, id_tRNA_SLVcst, 3, 2000, id_tRNA_SLVLV, 4, 
        3, id_tRNA_GISLV, 5, id_tRNA_SDLVcst, 4, instruction::MARKER, id_tRNA_INCLV,
        0, 4, id_tRNA_SDLVcst, 4, 0, id_tRNA_INCLV, 0,
        4, id_tRNA_SDLVLV, 4, 1, id_tRNA_INCLV, 0, 4, 
        id_tRNA_SDLVcst, 4, 0, id_tRNA_INCLV, 0, 4, id_tRNA_SDLVcst, 
        4, 0, id_tRNA_INCLV, 0, 4, id_tRNA_SDLVcst, 4, 
        0, id_tRNA_INCLV, 0, 4, id_tRNA_SDLVcst, 4, 0,
        id_tRNA_SLVcst, 8, 1, id_tRNA_IF0, 8, id_tRNA_INCLV, 0, 
        2, id_tRNA_INCLV, 0, 4, id_tRNA_CMPLVLV, 0, 2,
        5, 8, id_tRNA_INCLV, 1, 8, id_tRNA_IF0, 8,
        id_tRNA_GDIDLV, 2, 4, id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_SWJ, id_tRNA_SDLVcst,
        4, instruction::MARKER,  id_tRNA_INCLV, 0, 4, id_tRNA_SDLVcst, 4,
        0, id_tRNA_SDLVLV, 4, 1, id_tRNA_SDLVcst, 4, 0, 
        id_tRNA_INCLV, 0, 4, id_tRNA_SDLVcst, 4, 0, id_tRNA_INCLV, 
        0, 4, id_tRNA_SDLVcst, 4, 0, id_tRNA_INCLV, 0, 
        4, id_tRNA_SDLVcst, 4, 0, id_tRNA_INCLV, 0, 4, 
        id_tRNA_WGDLV, 6, 3, 4, id_tRNA_RET, GSTOP_ID, 0,


        // 201 - copy free genes into code as new func

        GSTART_ID, 300, id_tRNA_CVARS, LV_place, 9, id_tRNA_IVARS, id_tRNA_USLV,
        1, id_tRNA_SLVcst, 5, 0, id_tRNA_SLVcst, 9, 1,
        id_tRNA_IF0, 9, id_tRNA_CMPLVLV, 1, 5, 9, id_tRNA_IF0,
        9, id_tRNA_PCSWI, -1, id_tRNA_RET, id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_INCLV, 
        1, 9, id_tRNA_RULV, 5, id_tRNA_INCLV, 5, id_tRNA_GISLV, 
        2, id_tRNA_CMPLVcst, 5, 2, 2, 7, id_tRNA_IF0, 
        7, id_tRNA_GILV, 3, 0, id_tRNA_GILV, 4, 1,
        id_tRNA_CMPLVcst, 0, 3, 3, 7, id_tRNA_IF0, 7,
        id_tRNA_GTSLV, 6, id_tRNA_CMPLVLV, 0, 4, 6, 7, id_tRNA_CMPLVcst,
        6, -1, 8, id_tRNA_OPELVLV, 7, 8, id_tRNA_IF0,
        7, id_tRNA_PCSWI, 1, id_tRNA_RET, id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_SIJ, 
        id_tRNA_SEJ, id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_SWJ, id_tRNA_RET, GSTOP_ID, 0



    //---------- additional DNA

        // 2 - core switcher

    };

    return DNA;
}

void SelfCompilationEvoX::exec_step_1(sp_univ_evo_algos universe, sp_evox algo)
{
    //----- get Heaviside function

    std::vector<int> DNA = get_DNA_step_1();

    sp_freegenes freegenes = std::make_shared<FreeGenes>("free genes");
    freegenes->init();
    freegenes->set_genes(DNA);
    universe->get_places()[1]->set_entity(freegenes);

    algo->set_input({3, -1});
    universe->exec();

    //write_genes_to_csv(algo->get_genes(), "genes_with_bootstrap_DNA.csv");
}

//-------------------- step 2

