#include "SelfCompilationEvoX.hpp"

#include <fstream>

#include "../../../../../Utils/Functions.hpp"
#include "../../../../../Utils/Maths/RandomGen.hpp"
#include "../../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../../../../Models/EvoAlgos/X86Algo/FreeMolecules.hpp"



SelfCompilationEvoX::SelfCompilationEvoX()
    :Experiment::Experiment(name_exp_bioevo_phenotypic_body_evox_selfc)
{
    init();
}

void SelfCompilationEvoX::init()
{
    max_nb_instr_exec = 2<<22;
    nb_genes = 97;
}

void SelfCompilationEvoX::launch()
{
    sp_evox algo = get_base_algo(1);
    sp_univ_evo_algos univ = get_universe(algo);
    exec_step_1(univ, algo);

    algo = get_base_algo(2);
    univ = get_universe(algo);
    exec_step_2(univ, algo);

    // re-exec step 2 but with new phenotypic body
    algo = get_base_algo(3);
    univ = get_universe(algo);
    exec_step_3(univ, algo);
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

sp_evox SelfCompilationEvoX::get_base_algo(int step)
{
    // create algo
    sp_evox algo = std::make_shared<EvoX>("evox algo");
    algo->init();
    algo->set_max_nb_instr_exec(max_nb_instr_exec);

    // get phenotypic body from csv
    std::string file_algo = "phenotypic_body_base_self_transcription.csv";
    if(step == 2)
        file_algo = "phenotypic_body_with_bootstrap_DNA.csv";
    else if(step == 3)
        file_algo = "phenotypic_body_transcribed.csv";
    std::vector<int> phenotypic_body = get_phenotypic_body_from_csv(file_algo);
    algo->set_phenotypic_body(phenotypic_body);

    // set data stack at 150
    algo->set_data_at(99, 150);

    return algo;
}

//-------------------- step 1

std::vector<int> SelfCompilationEvoX::get_DNA_step_1()
{
    int LV_place = 125;

    std::vector<int> DNA {
        3, -1,

        
        // 103 - search and pick free molecules

        GSTART_ID, id_search_and_pick, id_tRNA_CVARS, LV_place, 1, id_tRNA_IVARS, id_tRNA_CALLcst,
        id_get_mol_in_input, id_tRNA_GTSLVD, 1, id_tRNA_IF0, 1, id_tRNA_CALLcst, id_cpy_mol_as_new_func,
        id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_RET, GSTOP_ID, 0, 0, 0,

        // 106 - mRNA meta-aggregator

        GSTART_ID, id_mRNA_meta_aggregator, id_tRNA_CVARS, LV_place, 9, id_tRNA_IVARS, id_tRNA_SP_GSPLV, 
        1, id_tRNA_SP_GSPLV, 2, id_tRNA_SP_GSPLV, 3, id_tRNA_OPELVcst, 0, 
        1, 2, id_tRNA_OPELVcst, 0, 2, 3, id_tRNA_OPELVcst, 
        0, 3, 4, id_tRNA_SDLVLV, 2, 3, id_tRNA_SDLVLV, 
        3, 3, id_tRNA_INCDLV, 0, 2, id_tRNA_INCDLV, 0, 
        3, id_tRNA_SLVDLV, 8, 1, id_tRNA_SLVDLV, 9, 2, 
        id_tRNA_CMPLVLV, 1, 9, 8, 5, id_tRNA_IF0, 5, 
        id_tRNA_SLVDLV, 4, 2, id_tRNA_SLVDLV, 4, 4, id_tRNA_CMPLVcst, 
        4, 4, id_begin_aggregators, 6, id_tRNA_CMPLVcst, 2, 4, 
        id_begin_mutators, 7, id_tRNA_OPELVLV, 2, 6, 7, id_tRNA_IF0, 
        6, id_tRNA_CALLLV, 4, id_tRNA_SP_GSPLV, 1, id_tRNA_SP_GSPLV, 2, 
        id_tRNA_GTSLV, 3, id_tRNA_OPELVcst, 0, 1, 2, id_tRNA_OPELVcst, 
        0, 2, 3, id_tRNA_OPELVcst, 0, 3, 4, 
        id_tRNA_SIJ, id_tRNA_OPELVcst, 1, 4, id_begin_mutators, id_tRNA_CMPLVcst, 4, 
        4, 0, 6, id_tRNA_CMPLVcst, 2, 4, 10000, 
        7, id_tRNA_OPELVLV, 2, 6, 7, id_tRNA_IF0, 6, 
        id_tRNA_INCDLV, 0, 2, id_tRNA_SLVDLV, 4, 2, id_tRNA_SLVDLV, 
        4, 4, id_tRNA_OPELVLV, 0, 2, 4, id_tRNA_SIJ, 
        id_tRNA_SLVDLV, 8, 2, id_tRNA_SLVDLV, 9, 3, id_tRNA_SDLVDLV, 
        9, 8, id_tRNA_INCDLV, 0, 2, id_tRNA_INCDLV, 0, 
        3, id_tRNA_SEJ, id_tRNA_SEJ, id_tRNA_SLVDLV, 8, 1, id_tRNA_SLVDLV, 
        9, 2, id_tRNA_CMPLVLV, 1, 9, 8, 5, 
        id_tRNA_SWJ, id_tRNA_SDLVDLV, 1, 3, id_tRNA_SDLVcst, 2, 0, 
        id_tRNA_SDLVcst, 3, 0, id_tRNA_RET, GSTOP_ID, 0, 0,


        // 107 - DNA meta-mutator

        GSTART_ID, id_DNA_metamutator, id_tRNA_CVARS, LV_place, 7, id_tRNA_IVARS, id_tRNA_SLVcst, 
        5, GSTART_ID-1, id_tRNA_INCLV, 0, 5, id_tRNA_SP_GSPLV, 6, 
        id_tRNA_INCLV, 0, 1, id_tRNA_SLVDLV, 6, 6, id_tRNA_SLVcst, 
        1, -7, id_tRNA_SLVcst, 3, 1, id_tRNA_IF0, 3, 
        id_tRNA_OPELVcst, 0, 1, 7, id_tRNA_RGLVLV, 2, 1, 
        id_tRNA_CMPLVcst, 0, 2, instruction::MARKER, 4, id_tRNA_IF0, 4, 
        id_tRNA_OPELVcst, 0, 1, 2, id_tRNA_RGLVLV, 2, 1, 
        id_tRNA_CMPLVcst, 0, 2, -1, 3, id_tRNA_INCLV, 1, 
        3, id_tRNA_OPELVcst, 1, 1, 2, id_tRNA_SIJ, id_tRNA_SEJ, 
        id_tRNA_SWJ, id_tRNA_SLVcst, 3, 1, id_tRNA_IF0, 3, id_tRNA_OPELVcst, 
        0, 1, 7, id_tRNA_RGLVLV, 2, 1, id_tRNA_CMPLVLV, 
        0, 2, 5, 4, id_tRNA_IF0, 4, id_tRNA_INCLV, 
        0, 1, id_tRNA_RGLVLV, 2, 1, id_tRNA_CMPLVLV, 0, 
        2, 6, 3, id_tRNA_INCLV, 1, 3, id_tRNA_INCLV, 
        1, 1, id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_SWJ, id_tRNA_INCLV, 0, 
        1, id_tRNA_SLVcst, 7, 0, id_tRNA_SLVcst, 3, 1, 
        id_tRNA_IF0, 3, id_tRNA_RGLVLV, 2, 1, id_tRNA_OPELVcst, 1, 
        2, id_begin_mutators, id_tRNA_CMPLVcst, 2, 2, 0, 3, 
        id_tRNA_CMPLVcst, 2, 2, 10000, 4, id_tRNA_OPELVLV, 2, 
        3, 4, id_tRNA_IF0, 3, id_tRNA_ScstLV, 99, 1, 
        id_tRNA_INCcst, 1, 99, id_tRNA_ScstLV, 99, 7, id_tRNA_CALLLV, 
        2, id_tRNA_SP_GSPLV, 1, id_tRNA_SP_GSPLV, 7, id_tRNA_INCLV, 1, 
        7, id_tRNA_SLVDLV, 1, 1, id_tRNA_SLVDLV, 7, 7, 
        id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_SLVcst, 5, GSTOP_ID-1, id_tRNA_INCLV, 0, 
        5, id_tRNA_INCLV, 0, 1, id_tRNA_RGLVLV, 2, 1, 
        id_tRNA_CMPLVLV, 0, 2, 5, 3, id_tRNA_INCLV, 1, 
        3, id_tRNA_SWJ, id_tRNA_IF0, 7, id_tRNA_INCLV, 1, 7, 
        id_tRNA_GADD, 1, 0, id_tRNA_INCLV, 0, 1, id_tRNA_SWJ, 
        id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0, 0, 

        // 200 - calc phenotypic body size

        GSTART_ID, id_phenotypic_size, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_SLVcst,
        1, 1, id_tRNA_SLVcst, 2, -7, id_tRNA_IF0, 1,
        id_tRNA_OPELVcst, 0, 2, 7, id_tRNA_RGLVLV, 3, 2,
        id_tRNA_CMPLVcst, 0, 3, instruction::MARKER, 1, id_tRNA_IF0, 1,
        id_tRNA_INCLV, 0, 2, id_tRNA_RGLVLV, 3, 2, id_tRNA_INCLV,
        1, 2, id_tRNA_CMPLVcst, 0, 2, -1, 1, 
        id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_INCLV, 1, 1, id_tRNA_SWJ, id_tRNA_OPELVcst,
        0, 2, 7, id_tRNA_GScstLV, 2, 2, id_tRNA_RET,
        GSTOP_ID, 0, 0, 0, 0, 0, 0,


        // 201 - copy free molecules into code as new func

        GSTART_ID, id_cpy_mol_as_new_func, id_tRNA_CVARS, LV_place, 9, id_tRNA_IVARS, id_tRNA_SLVcst,
        8, 1, id_tRNA_SLVcst, 6, 0, id_tRNA_IF0, 8, 
        id_tRNA_RGLVLV, 1, 6, id_tRNA_CMPLVcst, 0, 1, instruction::MARKER,
        7, id_tRNA_IF0, 7, id_tRNA_INCcst, 0, 6, id_tRNA_RGLVLV, 
        1, 6, id_tRNA_INCcst, 1, 6, id_tRNA_CMPLVcst, 0, 
        1, -1, 7, id_tRNA_IF0, 7, id_tRNA_SLVcst, 8, 
        0, id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_OPELVcst, 0, 
        6, 7, id_tRNA_SWJ, id_tRNA_GILV, 1, 1, id_tRNA_SLVcst, 
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
        id_tRNA_GDIDLV, 4, 2, id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_SWJ, id_tRNA_SDLVcst,
        4, instruction::MARKER,  id_tRNA_INCLV, 0, 4, id_tRNA_SDLVcst, 4,
        0, id_tRNA_INCLV, 0, 4, id_tRNA_SDLVLV, 4, 1, 
        id_tRNA_INCLV, 0, 4, id_tRNA_SDLVcst, 4, 0, id_tRNA_INCLV, 
        0, 4, id_tRNA_SDLVcst, 4, 0, id_tRNA_INCLV, 0, 
        4, id_tRNA_SDLVcst, 4, 0, id_tRNA_INCLV, 0, 4, 
        id_tRNA_SDLVcst, 4, 0, id_tRNA_INCLV, 0, 4, id_tRNA_WGDLV, 
        6, 3, 4, id_tRNA_RET, GSTOP_ID, 0, 0,


        // 300 - get free molecules in input

        GSTART_ID, id_get_mol_in_input, id_tRNA_CVARS, LV_place, 9, id_tRNA_IVARS, id_tRNA_USLV,
        1, id_tRNA_SLVcst, 5, 0, id_tRNA_SLVcst, 9, 1,
        id_tRNA_IF0, 9, id_tRNA_CMPLVLV, 0, 1, 5, 9, 
        id_tRNA_IF0, 9, id_tRNA_PCSWI, -1, id_tRNA_RET, id_tRNA_SIJ, id_tRNA_SEJ, 
        id_tRNA_INCLV, 1, 9, id_tRNA_RULV, 5, id_tRNA_INCLV, 0, 
        5, id_tRNA_GISLV, 2, id_tRNA_CMPLVcst, 5, 2, 2, 
        7, id_tRNA_IF0, 7, id_tRNA_GILV, 3, 0, id_tRNA_GILV, 
        4, 1,id_tRNA_CMPLVcst, 0, 3, 3, 7, 
        id_tRNA_IF0, 7,id_tRNA_GTSLV, 6, id_tRNA_CMPLVLV, 0, 4, 
        6, 7, id_tRNA_CMPLVcst, 0, 6, -1, 8, 
        id_tRNA_OPELVLV, 0, 7, 8, id_tRNA_IF0, 7, id_tRNA_PCSWI, 
        1, id_tRNA_RET, id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_SIJ, 
        id_tRNA_SEJ, id_tRNA_SWJ, id_tRNA_PCSWI, 0, id_tRNA_RET, GSTOP_ID, 0,


        // 301 - find empty place

        GSTART_ID, id_find_empty_place, id_tRNA_CVARS, LV_place, 4, id_tRNA_IVARS, id_tRNA_USLV, 
        1, id_tRNA_PCSI, -1, id_tRNA_SLVcst, 2, 0, id_tRNA_SLVcst, 
        3, 1, id_tRNA_IF0, 3, id_tRNA_EMPTY, 4, 2, 
        id_tRNA_INCLV, 1, 4, id_tRNA_INCLV, 0, 2, id_tRNA_IF0, 
        4, id_tRNA_CMPLVLV, 0, 2, 1, 3, id_tRNA_INCLV, 
        1, 3, id_tRNA_SIJ, id_tRNA_PLVSWI, 2, id_tRNA_SLVcst, 3, 
        0, id_tRNA_SEJ, id_tRNA_SWJ, id_tRNA_RET, GSTOP_ID, 0, 0,


    //---------- additional DNA

        // 2 - core switcher

        GSTART_ID, id_core_switcher, id_tRNA_CVARS, LV_place, 4, id_tRNA_IVARS, id_tRNA_SLVaddr, 
        1, 97, id_tRNA_CMPLVcst, 2, 1, 0, 2, 
        id_tRNA_IF0, 2, id_tRNA_CALLcst, id_self_compil_transcription, id_tRNA_RET,id_tRNA_SIJ, id_tRNA_SEJ, 
        id_tRNA_GISLV, 1, id_tRNA_CMPLVcst, 1, 1, 2, 2, 
        id_tRNA_IF0, 2, id_tRNA_RET, id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_GILV, 3, 
        0, id_tRNA_CMPLVcst, 0, 3, 3, 2, id_tRNA_IF0, 
        2, id_tRNA_GILV, 4, 1, id_tRNA_CALLcst, id_search_and_pick, id_tRNA_RET, 
        id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_CMPLVcst, 0, 3, 4, 2, 
        id_tRNA_IF0, 2, id_tRNA_GILV, 4, 1, id_tRNA_PLVSI, 4, 
        id_tRNA_CALLcst, id_export_func_as_mol, id_tRNA_INCcst, 1, 99, id_tRNA_RET, id_tRNA_SIJ, 
        id_tRNA_SEJ, id_tRNA_CMPLVcst, 0, 3, 5, 2, id_tRNA_IF0, 
        2, id_tRNA_CMPLVcst, 2, 1, 2, 2, id_tRNA_IF0, 
        2, id_tRNA_GILV, 4, 1, id_tRNA_PLVSI, 4, id_tRNA_GILV, 
        4, 2, id_tRNA_PLVSI, 4, id_tRNA_CALLcst, id_ml_core, id_tRNA_SIJ, 
        id_tRNA_SEJ, id_tRNA_RET, id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_GILV, 4, 1, 
        id_tRNA_CALLLV, 4, id_tRNA_RET, GSTOP_ID, 0, 0, 0,


        // 3 - ML core

        GSTART_ID, id_ml_core, id_tRNA_CVARS, LV_place, 4, id_tRNA_IVARS, id_tRNA_CALLcst, 
        id_DNA_checker, id_tRNA_GTSLV, 1, id_tRNA_INCcst, 1, 99, id_tRNA_GTSLV, 
        2, id_tRNA_IF0, 1, id_tRNA_CALLLV, 2, id_tRNA_SIJ, id_tRNA_CALLcst, 
        id_new_gene_processor, id_tRNA_SEJ, id_tRNA_RET, GSTOP_ID, 0, 0, 0,

        // 202 - func list manager

        //GSTART_ID, 202, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_GTSLV, 
        //1, id_tRNA_INCS, 0, id_tRNA_SLVcst, 3, 0, id_tRNA_CMPLVcst, 
        //0, 3, 0, 4, id_tRNA_IF0, 4, id_tRNA_INCS, 
        //1, id_tRNA_CALLcst, 203, id_tRNA_SIJ, id_tRNA_CMPLVcst, 0, 3, 
        //1, 4, id_tRNA_IF0, 4, id_tRNA_INCS, 1, id_tRNA_INCS, 
        //1, id_tRNA_CALLcst, 204, id_tRNA_SIJ, id_tRNA_CALLcst, 205, id_tRNA_GTSLV, 
        //1, id_tRNA_INCS, 1, id_tRNA_ScstLV, 99, 1, id_tRNA_SEJ, 
        //id_tRNA_SEJ, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0,

        // 203 - func list builder


        // 204 - func DNA checker

        GSTART_ID, id_DNA_checker, id_tRNA_CVARS, LV_place, 6, id_tRNA_IVARS, id_tRNA_CALLcst, 
        id_DNA_pos, id_tRNA_GTSLV, 1, id_tRNA_INCcst, 1, 99, id_tRNA_GTSLV, 
        4, id_tRNA_SLVcst, 5, GSTART_ID-1, id_tRNA_INCLV, 0, 5, 
        id_tRNA_SLVcst, 3, 1, id_tRNA_IF0, 3, id_tRNA_OPELVcst, 0, 
        1, 7, id_tRNA_RGLVLV, 2, 1, id_tRNA_CMPLVLV, 0, 
        2, 5, 3, id_tRNA_IF0, 3, id_tRNA_INCLV, 0, 
        1, id_tRNA_RGLVLV, 2, 1, id_tRNA_CMPLVLV, 0, 2, 
        4, 3, id_tRNA_INCLV, 1, 1, id_tRNA_IF0, 3, 
        id_tRNA_PLVSI, 1, id_tRNA_RET, id_tRNA_SIJ, id_tRNA_SLVcst, 3, 1, 
        id_tRNA_SEJ, id_tRNA_SIJ, id_tRNA_SLVcst, 3, 1, id_tRNA_CMPLVcst, 0, 
        2, instruction::MARKER, 3, id_tRNA_IF0, 3, id_tRNA_INCLV, 0, 
        1, id_tRNA_RGLVLV, 2, 1, id_tRNA_CMPLVcst, 0, 2, 
        0, 3, id_tRNA_INCLV, 1, 1, id_tRNA_IF0, 3, 
        id_tRNA_OPELVcst, 0, 1, 2, id_tRNA_RGLVLV, 2, 1, 
        id_tRNA_CMPLVcst, 0, 2, -1, 3, id_tRNA_INCLV, 1, 
        3, id_tRNA_OPELVcst, 0, 1, 2, id_tRNA_SIJ, id_tRNA_SLVcst, 
        3, 1, id_tRNA_SEJ, id_tRNA_SIJ, id_tRNA_SLVcst, 3, 1, 
        id_tRNA_SEJ, id_tRNA_SEJ, id_tRNA_SWJ, id_tRNA_SLVcst, 1, 0, id_tRNA_PLVSI, 
        1, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0,

        
        // 205 - DNA pos

        GSTART_ID, id_DNA_pos, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_SLVcst, 
        1, 0, id_tRNA_SLVcst, 3, 1, id_tRNA_IF0, 3, 
        id_tRNA_OPELVcst, 0, 1, 7, id_tRNA_RGLVLV, 2, 1, 
        id_tRNA_CMPLVcst, 0, 2, instruction::MARKER, 4, id_tRNA_IF0, 4, 
        id_tRNA_OPELVcst, 0, 1, 2, id_tRNA_RGLVLV, 2, 1, 
        id_tRNA_CMPLVcst, 0, 2, -1, 3, id_tRNA_INCLV, 1, 
        3, id_tRNA_OPELVcst, 1, 1, 2, id_tRNA_SIJ, id_tRNA_SEJ, 
        id_tRNA_SWJ, id_tRNA_PLVSI, 1, id_tRNA_RET, GSTOP_ID, 0, 0,


        // 208 - transcriber

        GSTART_ID, id_transcriber, id_tRNA_CVARS, LV_place, 6, id_tRNA_IVARS, id_tRNA_GILV,
        1, 2, id_tRNA_PLVSI, 1, id_tRNA_CALLcst, id_RNAP, id_tRNA_CALLcst,
        116, id_tRNA_CALLcst, id_ribosome, id_tRNA_SP_GSPLV, 2, id_tRNA_OPELVcst, 0, 
        2, 3, id_tRNA_SLVLV, 3, 2, id_tRNA_SLVcst, 2, 
        instruction::MARKER, id_tRNA_INCLV, 0, 2, id_tRNA_SDLVcst, 2, 0, 
        id_tRNA_INCLV, 0, 2, id_tRNA_GTSDLV, 2, id_tRNA_INCLV, 0, 
        2, id_tRNA_SDLVcst, 2, 0, id_tRNA_INCLV, 0, 2, 
        id_tRNA_SDLVcst, 2, 0, id_tRNA_INCLV, 0, 2, id_tRNA_SDLVcst, 
        2, 0, id_tRNA_INCLV, 0, 2, id_tRNA_SDLVcst, 2, 
        0, id_tRNA_SP_GSPLV, 2, id_tRNA_OPELVcst, 0, 2, 2, 
        id_tRNA_SLVDLV, 2, 2, id_tRNA_INCLV, 0, 2, id_tRNA_SLVcst, 
        2, instruction::MARKER, id_tRNA_INCLV, 0, 2, id_tRNA_SDLVcst, 2, 
        0, id_tRNA_INCLV, 0, 2, id_tRNA_GTSDLV, 2, id_tRNA_INCLV, 
        0, 2, id_tRNA_SDLVcst, 2, 0, id_tRNA_INCLV, 0, 
        2, id_tRNA_SDLVcst, 2, 0, id_tRNA_INCLV, 0, 2, 
        id_tRNA_SDLVcst, 2, 0, id_tRNA_INCLV, 0, 2, id_tRNA_SDLVcst, 
        2, 0, id_tRNA_SLVcst, 5, -7, id_tRNA_SLVcst, 4, 
        1, id_tRNA_IF0, 4, id_tRNA_OPELVcst, 0, 5, 7, 
        id_tRNA_RGLVLV, 4, 5, id_tRNA_CMPLVcst, 0, 4, instruction::MARKER, 
        6, id_tRNA_IF0, 6, id_tRNA_INCLV, 0, 5, id_tRNA_RGLVLV, 
        4, 5, id_tRNA_CMPLVcst, 0, 4, -1, 4, 
        id_tRNA_INCLV, 1, 4, id_tRNA_INCLV, 1, 5, id_tRNA_SIJ, 
        id_tRNA_SEJ, id_tRNA_SWJ, id_tRNA_SP_GCPY, 5, 3, 2, id_tRNA_RET, 
        GSTOP_ID, 0, 0, 0, 0, 0, 0,

        // 207 RNAP

        GSTART_ID, id_RNAP, id_tRNA_CVARS, LV_place, 6, id_tRNA_IVARS, id_tRNA_SLVcst,
        1, -7, id_tRNA_SLVcst, 3, 1, id_tRNA_IF0, 3, 
        id_tRNA_OPELVcst, 0, 1, 7, id_tRNA_RGLVLV, 2, 1, 
        id_tRNA_CMPLVcst, 0, 2, instruction::MARKER, 4, id_tRNA_IF0, 4, 
        id_tRNA_OPELVcst, 0, 1, 2, id_tRNA_RGLVLV, 2, 1, 
        id_tRNA_CMPLVcst, 0, 2, -1, 3, id_tRNA_INCLV, 1, 
        3, id_tRNA_OPELVcst, 1, 1, 2, id_tRNA_SIJ, id_tRNA_SEJ, 
        id_tRNA_SWJ, id_tRNA_SLVcst, 6, GSTART_ID-1, id_tRNA_INCLV, 0, 6, 
        id_tRNA_GTSLV, 4, id_tRNA_SLVcst, 3, 1, id_tRNA_IF0, 3, 
        id_tRNA_OPELVcst, 0, 1, 7, id_tRNA_RGLVLV, 2, 1,  
        id_tRNA_CMPLVLV, 0, 6, 2, 5, id_tRNA_IF0, 5, 
        id_tRNA_INCLV, 0, 1, id_tRNA_RGLVLV, 2, 1, id_tRNA_CMPLVLV, 
        0, 2, 4, 3, id_tRNA_INCLV, 1, 3, 
        id_tRNA_INCLV, 1, 1, id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_SWJ, id_tRNA_INCcst, 
        0, 99, id_tRNA_SP_GSPLV, 2, id_tRNA_INCLV, 0, 2, 
        id_tRNA_SDLVcst, 2, 0, id_tRNA_INCLV, 0, 2, id_tRNA_SDLVcst, 
        2, 0, id_tRNA_INCLV, 0, 1, id_tRNA_SLVcst, 6, 
        GSTOP_ID-1, id_tRNA_INCLV, 0, 6, id_tRNA_SLVcst, 3, 1, 
        id_tRNA_IF0, 3, id_tRNA_INCLV, 0, 1, id_tRNA_INCLV, 0, 
        2, id_tRNA_RGLVLV, 5, 1, id_tRNA_SDLVLV, 2, 5, 
        id_tRNA_SLVDLV, 3, 2, id_tRNA_CMPLVLV, 0, 3, 6, 
        3, id_tRNA_INCLV, 1, 3, id_tRNA_SWJ, id_tRNA_INCLV, 1, 
        2, id_tRNA_PLVSWI, 2, id_tRNA_INCcst, 1, 99, id_tRNA_INCcst, 
        1, 99, id_tRNA_PLVSWI, 4, id_tRNA_RET, GSTOP_ID, 0, 



        // 206 ribosome

        GSTART_ID, id_ribosome, id_tRNA_CVARS, LV_place, 6, id_tRNA_IVARS, id_tRNA_INCcst, 
        0, 99, id_tRNA_INCcst, 0, 99, id_tRNA_GTSLV, 1, 
        id_tRNA_INCLV, 0, 1, id_tRNA_SDLVLV, 1, 1, id_tRNA_SP_GSPLV, 
        1, id_tRNA_INCLV, 0, 1, id_tRNA_SDLVLV, 1, 1, 
        id_tRNA_SLVDLV, 2, 1, id_tRNA_OPELVcst, 0, 2, 2, 
        id_tRNA_SDLVLV, 1, 2,id_tRNA_SP_GSPLV, 1, id_tRNA_INCLV, 0, 
        1, id_tRNA_SLVDLV, 4, 1, id_tRNA_GTSLV, 5, id_tRNA_CMPLVLV, 
        3, 4, 5, 2, id_tRNA_IF0, 2, id_tRNA_INCcst, 
        0, 99, id_tRNA_SLVDLV, 3, 1, id_tRNA_SLVDLV, 3, 
        3, id_tRNA_CALLLV, 3, id_tRNA_INCcst, 1, 99, id_tRNA_SP_GSPLV, 
        1, id_tRNA_INCLV, 0, 1, id_tRNA_SLVDLV, 4, 1, 
        id_tRNA_GTSLV, 5, id_tRNA_CMPLVLV, 3, 4, 5, 2, 
        id_tRNA_SWJ, id_tRNA_GTSLV, 1, id_tRNA_INCLV, 0, 1, id_tRNA_SLVDLV, 
        2, 1, id_tRNA_SLVDLV, 3, 1, id_tRNA_OPELVLV, 1, 
        3, 1, id_tRNA_SP_GSPLV, 4, id_tRNA_OPELVLV, 0, 4, 
        3, id_tRNA_PLVSWI, 4, id_tRNA_SP_GSPLV, 6, id_tRNA_OPELVcst, 0, 
        6, 7, id_tRNA_CMPLVLV, 1, 1, 2, 7, 
        id_tRNA_IF0, 7, id_tRNA_INCLV, 0, 1, id_tRNA_INCLV, 0, 
        6, id_tRNA_SDLVDLV, 6, 1, id_tRNA_CMPLVLV, 1, 1, 
        2, 7, id_tRNA_SWJ, id_tRNA_GTSLV, 4, id_tRNA_OPELVcst, 0, 
        4, 7, id_tRNA_PLVSWI, 4, id_tRNA_INCcst, 1, 99, 
        id_tRNA_INCcst, 1, 99, id_tRNA_RET, GSTOP_ID, 0, 0,

        // 104 self compilation - func ID list

        GSTART_ID, id_self_compil_func_ID_list, id_tRNA_CVARS, LV_place, 6, id_tRNA_IVARS, id_tRNA_INCcst, 
        0, 99, id_tRNA_SLVcst,1, -7, id_tRNA_SLVcst, 3, 
        1, id_tRNA_IF0, 3, id_tRNA_OPELVcst, 0, 1, 7, 
        id_tRNA_RGLVLV, 2, 1, id_tRNA_CMPLVcst, 0, 2, instruction::MARKER, 
        4, id_tRNA_IF0, 4, id_tRNA_OPELVcst, 0, 1, 2, 
        id_tRNA_RGLVLV, 2, 1, id_tRNA_CMPLVcst, 0, 2, -1, 
        3, id_tRNA_INCLV, 1, 3, id_tRNA_OPELVcst, 1, 1, 
        2, id_tRNA_SIJ, id_tRNA_SEJ,id_tRNA_SWJ, id_tRNA_OPEcstcst, 0, 99, 
        3, id_tRNA_PCSWI, 0, id_tRNA_SLVaddr, 5, 99, id_tRNA_SLVcst, 
        3, 1, id_tRNA_IF0, 3, id_tRNA_OPELVcst, 0, 1, 
        7, id_tRNA_RGLVLV, 2, 1, id_tRNA_CMPLVcst, 0, 2, 
        instruction::MARKER, 4, id_tRNA_IF0, 4, id_tRNA_OPELVcst, 0, 1, 
        2, id_tRNA_RGLVLV, 2, 1, id_tRNA_CMPLVcst, 0, 2, 
        -1, 3, id_tRNA_INCLV, 1, 3, id_tRNA_OPELVcst, 1, 
        1, 2, id_tRNA_SIJ, id_tRNA_SLVcst, 6, GSTART_ID-1, id_tRNA_INCLV, 
        0, 6, id_tRNA_CMPLVLV, 0, 2, 6, 4, 
        id_tRNA_IF0, 4, id_tRNA_INCLV, 0, 1, id_tRNA_INCLV, 0, 
        5, id_tRNA_INCS, 0, id_tRNA_RGLVLV, 6, 1, id_tRNA_SDLVLV, 
        5, 6, id_tRNA_INCLV, 1, 1, id_tRNA_SIJ, id_tRNA_SEJ, 
        id_tRNA_SEJ, id_tRNA_SWJ, id_tRNA_SP_GSPLV, 6, id_tRNA_GTSLV, 5, id_tRNA_OPELVLV, 
        0, 6, 5, id_tRNA_INCLV, 0, 6, id_tRNA_INCcst, 
        1, 99, id_tRNA_PLVSWI, 6, id_tRNA_INCcst, 1, 99, 
        id_tRNA_PLVSWI, 6, id_tRNA_OPEcstcst, 1, 99, 2, id_tRNA_ScstLV, 
        97, 5, id_tRNA_INCcst, 0, 97, id_tRNA_RET, GSTOP_ID,

        // 105 self compilation - transcription

        GSTART_ID, id_self_compil_transcription, id_tRNA_CVARS, LV_place, 10, id_tRNA_IVARS, id_tRNA_OPEcstcst, 
        0, 99, 2, id_tRNA_GTSLV, 1, id_tRNA_INCcst, 0, 
        99, id_tRNA_GTSLV, 2, id_tRNA_INCcst, 0, 99, id_tRNA_GTSLV, 
        3, id_tRNA_IF0, 3, id_tRNA_SLVaddr, 4, 99, id_tRNA_OPELVLV, 
        0, 3, 4, id_tRNA_SLVDLV, 5, 3, id_tRNA_INCLV, 
        0, 3, id_tRNA_SDLVLV, 2, 4, id_tRNA_ScstLV, 99, 
        2, id_tRNA_PLVSI, 5, id_tRNA_PLVSI, 5, id_tRNA_CALLcst, id_DNA_metamutator, 
        id_tRNA_CALLcst, id_RNAP, id_tRNA_CALLcst, id_mRNA_meta_aggregator, id_tRNA_CALLcst, id_ribosome, id_tRNA_GTSLV, 
        3, id_tRNA_INCcst, 1, 99, id_tRNA_GTSLV, 4, id_tRNA_OPEcstcst, 
        0, 99, 3, id_tRNA_GTSLV, 2, id_tRNA_INCLV, 0, 
        2, id_tRNA_ScstLV, 99, 4, id_tRNA_INCS, 1, id_tRNA_INCcst, 
        1, 99, id_tRNA_INCS, 1, id_tRNA_INCcst, 1, 97, 
        id_tRNA_GTSLV, 1, id_tRNA_SDLVcst, 1, instruction::MARKER, id_tRNA_INCLV, 0, 
        1, id_tRNA_SDLVcst, 1, 0, id_tRNA_INCLV, 0, 1, 
        id_tRNA_SDLVLV, 1, 3, id_tRNA_INCLV, 0, 1, id_tRNA_SDLVcst, 
        1, 0, id_tRNA_INCLV, 0, 1, id_tRNA_SDLVcst, 1, 
        0, id_tRNA_INCLV, 0, 1, id_tRNA_SDLVcst, 1, 0, 
        id_tRNA_INCLV, 0, 1, id_tRNA_SDLVcst, 1, 0, id_tRNA_INCLV, 
        0, 1, id_tRNA_SLVLV, 5, 1, id_tRNA_OPELVcst, 0, 
        5, 5, id_tRNA_CMPLVLV, 0, 5, 2, 6, 
        id_tRNA_INCLV, 1, 6, id_tRNA_IF0, 6, id_tRNA_SDLVDLV, 1, 
        5, id_tRNA_INCLV, 0, 1, id_tRNA_INCLV, 0, 5, 
        id_tRNA_CMPLVLV, 0, 5, 2, 6, id_tRNA_INCLV, 1, 
        6, id_tRNA_SWJ, id_tRNA_SDLVcst, 1, instruction::MARKER, id_tRNA_INCLV, 0, 
        1, id_tRNA_SDLVcst, 1, 0, id_tRNA_INCLV, 0, 1, 
        id_tRNA_SDLVLV, 1, 3, id_tRNA_INCLV, 0, 1, id_tRNA_SDLVcst, 
        1, 0, id_tRNA_INCLV, 0, 1, id_tRNA_SDLVcst, 1, 
        0, id_tRNA_INCLV, 0, 1, id_tRNA_SDLVcst, 1, 0, 
        id_tRNA_INCLV, 0, 1, id_tRNA_SDLVcst, 1, 0, id_tRNA_INCLV, 
        0, 1, id_tRNA_SDLVcst, 1, 0, id_tRNA_INCLV, 0, 
        1, id_tRNA_PLVSWI, 1, id_tRNA_OPEcstcst, 1, 99, 3, 
        id_tRNA_SIJ, id_tRNA_CMPLVcst, 0, 3, -1, 9, id_tRNA_IF0, 
        9, id_tRNA_RET, id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_PLVSI, 1, id_tRNA_PLVSI, 
        2, id_tRNA_CALLcst, id_find_empty_place, id_tRNA_GTSLVD, 10, id_tRNA_GTSLVD, 2, 
        id_tRNA_GTSLVD, 1, id_tRNA_CMPLVcst, 0, 10, -1, 9, 
        id_tRNA_IF0, 9, id_tRNA_RET, id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_INCcst, 1, 
        99, id_tRNA_GTSLV, 2, id_tRNA_GTSLV, 7, id_tRNA_INCcst, 1, 
        99, id_tRNA_GTSLV, 1, id_tRNA_INCLV, 1, 1, id_tRNA_INCLV, 
        1, 2, id_tRNA_OPELVLV, 1, 7, 1, id_tRNA_SLVcst, 
        3, -7, id_tRNA_SLVcst, 9, 1, id_tRNA_IF0, 9, 
        id_tRNA_OPELVcst, 0, 3, 7, id_tRNA_RGLVLV, 5, 3, 
        id_tRNA_CMPLVcst, 0, 5, instruction::MARKER, 6, id_tRNA_IF0, 6, 
        id_tRNA_OPELVcst, 0, 3, 2, id_tRNA_RGLVLV, 5, 3, 
        id_tRNA_CMPLVcst, 0, 5, -1, 9, id_tRNA_INCLV, 1, 
        9, id_tRNA_OPELVcst, 1, 3, 2, id_tRNA_SIJ, id_tRNA_SEJ, 
        id_tRNA_SWJ, id_tRNA_SLVLV, 4, 3, id_tRNA_SLVcst, 9, 1, 
        id_tRNA_IF0, 9, id_tRNA_OPELVcst, 0, 4, 7, id_tRNA_RGLVLV, 
        5, 4, id_tRNA_CMPLVcst, 0, 5, instruction::MARKER, 6, 
        id_tRNA_IF0, 6, id_tRNA_OPELVcst, 0, 4, 2, id_tRNA_RGLVLV, 
        5, 4, id_tRNA_CMPLVcst, 0, 5, -1, 9, 
        id_tRNA_INCLV, 1, 9, id_tRNA_OPELVcst, 1, 4, 2, 
        id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_SWJ, id_tRNA_OPELVcst, 0, 4, 6, 
        id_tRNA_SLVLV, 8, 4, id_tRNA_OPELVLV, 1, 8, 3, 
        id_tRNA_INCLV, 0, 8, id_tRNA_OPELVcst, 0, 7, 28, 
        id_tRNA_OPELVLV, 0, 7, 8, id_tRNA_SOSLV, 7, id_tRNA_SLVcst, 
        6, 0, id_tRNA_SLVcst, 5, GGENESIS_ID, id_tRNA_GLVO, 6, 
        5, id_tRNA_OPELVcst, 0, 6, 2, id_tRNA_SLVcst, 5, 
        3, id_tRNA_GLVO, 6, 5, id_tRNA_INCLV, 0, 6, 
        id_tRNA_GLVO, 6, 7, id_tRNA_INCLV, 0, 6, id_tRNA_SLVcst, 
        5, 150, id_tRNA_GLVO, 6, 5, id_tRNA_INCLV, 0, 
        6, id_tRNA_SLVcst, 5, -1, id_tRNA_GLVO, 6, 5, 
        id_tRNA_OPELVcst, 0, 6, 3, id_tRNA_SLVcst, 5, 19, 
        id_tRNA_GLVO, 6, 5, id_tRNA_OPELVcst, 0, 6, 4, 
        id_tRNA_SLVcst, 5, 36, id_tRNA_GLVO, 6, 5, id_tRNA_OPELVcst, 
        0, 6, 3, id_tRNA_OPELVLV, 1, 7, 8, 
        id_tRNA_OPELVcst, 1, 7, 28, id_tRNA_SLVLV, 7, 1, 
        id_tRNA_CMPLVLV, 0, 7, 2, 5, id_tRNA_INCLV, 1, 
        5, id_tRNA_IF0, 5, id_tRNA_SLVDLV, 5, 7, id_tRNA_GLVO, 
        6, 5, id_tRNA_INCLV, 0, 7, id_tRNA_INCLV, 0, 
        6, id_tRNA_CMPLVLV, 0, 7, 2, 5, id_tRNA_INCLV, 
        1, 5, id_tRNA_SWJ, id_tRNA_SLVLV, 7, 3, id_tRNA_CMPLVLV, 
        0, 7, 4, 5, id_tRNA_INCLV, 1, 5, 
        id_tRNA_IF0, 5, id_tRNA_RGLVLV, 5, 7, id_tRNA_GLVO, 6, 
        5, id_tRNA_INCLV, 0, 7, id_tRNA_INCLV, 0, 6, 
        id_tRNA_CMPLVLV, 0, 7, 4, 5, id_tRNA_INCLV, 1, 
        5, id_tRNA_SWJ, id_tRNA_INCLV, 0, 6, id_tRNA_SLVcst, 5, 
        46, id_tRNA_GLVO, 6, 5, id_tRNA_INCLV, 0, 6, 
        id_tRNA_SLVcst, 5, -1, id_tRNA_GLVO, 6, 5, id_tRNA_WRITE, 
        9, 10, id_tRNA_INCS, 1, id_tRNA_INCcst, 1, 97, 
        id_tRNA_RET, id_tRNA_SEJ, id_tRNA_RET, GSTOP_ID, 0, 0, 0,


        // 303 - new gene processor

        GSTART_ID, id_new_gene_processor, id_tRNA_CVARS, LV_place, 8, id_tRNA_IVARS, id_tRNA_CALLcst, 
        id_DNA_pos, id_tRNA_GTSLV, 1, id_tRNA_INCcst, 1, 99, id_tRNA_GTSLV, 
        2, id_tRNA_SLVcst, 3, 1, id_tRNA_IF0, 3, id_tRNA_OPELVcst, 
        0, 1, 7, id_tRNA_RGLVLV, 4, 1, id_tRNA_CMPLVcst, 
        0, 4, instruction::MARKER, 5, id_tRNA_IF0, 5, id_tRNA_OPELVcst, 
        0, 1, 2, id_tRNA_RGLVLV, 4, 1, id_tRNA_CMPLVcst, 
        0, 4, -1, 3, id_tRNA_INCLV, 1, 3, 
        id_tRNA_OPELVcst, 1, 1, 2, id_tRNA_SIJ, id_tRNA_SEJ, id_tRNA_SWJ, 
        id_tRNA_SP_GSPLV, 6, id_tRNA_SP_GSPLV, 7, id_tRNA_SDLVcst, 7, GSTART_ID-1, 
        id_tRNA_INCDLV, 0, 7, id_tRNA_INCLV, 0, 7, id_tRNA_SDLVLV, 
        7, 2, id_tRNA_INCLV, 0, 7, id_tRNA_SDLVcst, 7, 
        id_tRNA_CVARS, id_tRNA_INCLV, 0, 7, id_tRNA_SDLVcst, 7, LV_place, 
        id_tRNA_INCLV, 0, 7, id_tRNA_SDLVcst, 7, 1, id_tRNA_INCLV, 
        0, 7, id_tRNA_SDLVcst, 7, id_tRNA_IVARS, id_tRNA_INCLV, 0, 
        7, id_tRNA_SDLVcst, 7, id_tRNA_RET, id_tRNA_INCLV, 0, 7, 
        id_tRNA_SDLVcst, 7, GSTOP_ID-1, id_tRNA_INCDLV, 0, 7, id_tRNA_INCLV, 
        0, 7, id_tRNA_SDLVcst, 7, 0, id_tRNA_INCLV, 0, 
        7, id_tRNA_SDLVcst, 7, 0, id_tRNA_INCLV, 0, 7, 
        id_tRNA_SDLVcst, 7, 0, id_tRNA_INCLV, 0, 7, id_tRNA_SDLVcst, 
        7, 0, id_tRNA_INCLV, 0, 7, id_tRNA_SDLVcst, 7, 
        0, id_tRNA_INCLV, 0, 7, id_tRNA_SDLVcst, 7, 0, 
        id_tRNA_SP_GCPY, 1, 6, 7, id_tRNA_CALLcst, id_self_compil_func_ID_list, id_tRNA_RET, 
        GSTOP_ID, 0, 0, 0, 0, 0, 0,


        //---------- mutators

        // mut_RUI

        GSTART_ID, id_mut_RUI, id_tRNA_CVARS, LV_place, 8, id_tRNA_IVARS, id_tRNA_SP_GSPLV, 
        1, id_tRNA_SP_GSPLV, 7, id_tRNA_INCLV, 1, 7, id_tRNA_SLVDLV, 
        1, 1, id_tRNA_SLVDLV, 7, 7, id_tRNA_SLVcst, 4, 
        0, id_tRNA_INCLV, 0, 1, id_tRNA_RGLVLV, 2, 1, 
        id_tRNA_CMPLVcst, 0, 2, -2, 3, id_tRNA_IF0, 3, 
        id_tRNA_GScstLV, 0, 1, id_tRNA_INCLV, 0, 1, id_tRNA_RGLVLV, 
        2, 1, id_tRNA_OPELVcst, 2, 2, 2, id_tRNA_GSLVLV, 
        2, 1, id_tRNA_OPELVLV, 0, 7, 2, id_tRNA_OPELVcst, 
        2, 2, 3, id_tRNA_SLVLV, 5, 1, id_tRNA_INCLV, 
        0, 5, id_tRNA_CMPLVLV, 1, 2, 4, 3, 
        id_tRNA_IF0, 3, id_tRNA_INCLV, 0, 1, id_tRNA_GADD, -1, 
        1, id_tRNA_INCLV, 0, 1, id_tRNA_GADD, 1, 1, 
        id_tRNA_INCLV, 0, 4, id_tRNA_CMPLVLV, 1, 4, 2, 
        3, id_tRNA_SWJ, id_tRNA_SLVLV, 3, 5, id_tRNA_SIJ, id_tRNA_INCLV, 
        0, 1, id_tRNA_RGLVLV, 2, 1, id_tRNA_SLVLV, 5, 
        1, id_tRNA_INCLV, 0, 5, id_tRNA_CMPLVLV, 1, 2, 
        4, 3, id_tRNA_IF0, 3, id_tRNA_INCLV, 0, 1, 
        id_tRNA_INCLV, 0, 4, id_tRNA_CMPLVLV, 1, 4, 2, 
        3, id_tRNA_SWJ, id_tRNA_SLVLV, 3, 5, id_tRNA_SEJ, id_tRNA_SLVcst, 
        8, 1, id_tRNA_IF0, 8, id_tRNA_RGLVLV, 5, 3, 
        id_tRNA_INCLV, 0, 3, id_tRNA_RGLVLV, 6, 3, id_tRNA_INCLV, 
        0, 3, id_tRNA_INCLV, 1, 2, id_tRNA_RUILVLV, 4, 
        5, 6, id_tRNA_RGLVLV, 5, 1, id_tRNA_OPELVLV, 0, 
        5, 4, id_tRNA_GSLVLV, 5, 1, id_tRNA_INCLV, 0, 
        1, id_tRNA_CMPLVcst, 2, 2, 0, 8, id_tRNA_SWJ, 
        id_tRNA_SLVLV, 1, 3, id_tRNA_ScstLV, 99, 1, id_tRNA_INCcst, 
        1, 99, id_tRNA_ScstLV, 99, 7, id_tRNA_RET, GSTOP_ID, 


        //---------- tRNAs

        // tRNA_CVARS

        GSTART_ID, id_tRNA_CVARS, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_SLVDLV, 2, 1, id_tRNA_SLVDLV, 2, 2, id_tRNA_ScstLV, 
        98, 2, id_tRNA_INCDLV, 0, 1, id_tRNA_SLVDLV, 3, 1, 
        id_tRNA_SDLVDLV, 2, 3, id_tRNA_INCDLV, 0, 1, 
        id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0, 0,

        // tRNA_IVARS

        GSTART_ID, id_tRNA_IVARS, id_tRNA_CVARS, LV_place, 5, id_tRNA_IVARS, id_tRNA_MP,
        id_tRNA_SLVaddr, 2, 98, id_tRNA_SLVLV, 3, 2, id_tRNA_SLVDLV,
        4, 2, id_tRNA_OPELVLV, 0, 3, 4, id_tRNA_SLVcst, 
        4, 100, id_tRNA_CMPLVLV, 1, 2, 3, 5, 
        id_tRNA_IF0, 5, id_tRNA_INCLV, 0, 2, id_tRNA_SDLVLV, 2, 
        4, id_tRNA_INCLV, 0, 4, id_tRNA_CMPLVLV, 1, 2, 
        3, 5, id_tRNA_SWJ, id_tRNA_RET, GSTOP_ID, 0, 0,

        // tRNA_SLVcst

        GSTART_ID, id_tRNA_SLVcst, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MCPY, id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, id_tRNA_MLV, id_tRNA_Marg, 
        id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0, 

        // tRNA_SDLVcst

        GSTART_ID, id_tRNA_SDLVcst, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MCPY, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, id_tRNA_MLV, id_tRNA_Marg, 
        id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0, 

        // tRNA_SLVLV

        GSTART_ID, id_tRNA_SLVLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MCPY, id_tRNA_M1, id_tRNA_M1, id_tRNA_M0, id_tRNA_MLV, id_tRNA_MLV, 
        id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0, 

        // tRNA_SDLVLV

        GSTART_ID, id_tRNA_SDLVLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MCPY, id_tRNA_M2, id_tRNA_M1, id_tRNA_M0, id_tRNA_MLV, id_tRNA_MLV, 
        id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0, 

        // tRNA_SLVDLV

        GSTART_ID, id_tRNA_SLVDLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MCPY, id_tRNA_M1, id_tRNA_M2, id_tRNA_M0, id_tRNA_MLV, id_tRNA_MLV, 
        id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0, 

        // tRNA_SDLVDLV

        GSTART_ID, id_tRNA_SDLVDLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MCPY, id_tRNA_M2, id_tRNA_M2, id_tRNA_M0, id_tRNA_MLV, id_tRNA_MLV, 
        id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0, 

        // tRNA_ScstLV

        GSTART_ID, id_tRNA_ScstLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MCPY, id_tRNA_M1, id_tRNA_M1, id_tRNA_M0, id_tRNA_Marg, id_tRNA_MLV, 
        id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0, 

        // tRNA_SLVaddr

        GSTART_ID, id_tRNA_SLVaddr, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MCPY, id_tRNA_M1, id_tRNA_M1, id_tRNA_M0, id_tRNA_MLV, id_tRNA_Marg, 
        id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0,

        // tRNA_RGLVLV

        GSTART_ID, id_tRNA_RGLVLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::GR, id_tRNA_M1, id_tRNA_M2, id_tRNA_M0, id_tRNA_MLV, 
        id_tRNA_MLV, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_GADD

        GSTART_ID, id_tRNA_GADD, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::GADD, id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, id_tRNA_MLV, 
        id_tRNA_Marg, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0,

        // tRNA_WGDLV

        GSTART_ID, id_tRNA_WGDLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::GCPY, id_tRNA_M2, id_tRNA_M2, id_tRNA_M2, id_tRNA_MLV, 
        id_tRNA_MLV, id_tRNA_MLV, id_tRNA_RET, GSTOP_ID, 0, 0, 0,

        // tRNA_GILV

        GSTART_ID, id_tRNA_GILV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::CPYIN, id_tRNA_M1, id_tRNA_M1, id_tRNA_M0, id_tRNA_MLV, 
        id_tRNA_Marg, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_GDILV

        GSTART_ID, id_tRNA_GDILV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::CPYIN, id_tRNA_M1, id_tRNA_M2, id_tRNA_M0, id_tRNA_MLV, 
        id_tRNA_Marg, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_GIDLV

        GSTART_ID, id_tRNA_GDILV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::CPYIN, id_tRNA_M2, id_tRNA_M1, id_tRNA_M0, id_tRNA_MLV, 
        id_tRNA_Marg, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_GDIDLV

        GSTART_ID, id_tRNA_GDIDLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::CPYIN, id_tRNA_M2, id_tRNA_M2, id_tRNA_M0, id_tRNA_MLV, 
        id_tRNA_Marg, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_GTSLV

        GSTART_ID, id_tRNA_GTSLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MCPY, id_tRNA_M1, id_tRNA_M2, id_tRNA_M0, id_tRNA_MLV, id_tRNA_Mcst, 
        99, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_GTSLVD

        GSTART_ID, id_tRNA_GTSLVD, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MCPY, id_tRNA_M1, id_tRNA_M2, id_tRNA_M0, id_tRNA_MLV, id_tRNA_Mcst, 
        99, id_tRNA_M0, id_tRNA_MInstr, instruction::DEC, id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_Mcst, 99, id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 

        // tRNA_GTSDLV

        GSTART_ID, id_tRNA_GTSDLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MCPY, id_tRNA_M2, id_tRNA_M2, id_tRNA_M0, id_tRNA_MLV, id_tRNA_Mcst, 
        99, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_GLVO

        GSTART_ID, id_tRNA_GLVO, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::CPYOUT, id_tRNA_M2, id_tRNA_M1, id_tRNA_M0, id_tRNA_MLV, 
        id_tRNA_MLV, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_IFO

        GSTART_ID, id_tRNA_IF0, id_tRNA_CVARS, LV_place, 4, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::JRE, id_tRNA_M0, id_tRNA_M1, id_tRNA_M0, id_tRNA_Mcst, 
        -142857, id_tRNA_MLV, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 

        // tRNA_SIJ

        GSTART_ID, id_tRNA_SIJ, id_tRNA_CVARS, LV_place, 6, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::JRA, id_tRNA_M0, id_tRNA_M0, id_tRNA_M0, id_tRNA_INCDLV, 
        0, 2, id_tRNA_SLVDLV, 4, 2, id_tRNA_SDLVcst, 4, 
        -285714, id_tRNA_M0, id_tRNA_M0, id_tRNA_SLVDLV, 3, 2, id_tRNA_SLVcst, 
        5, 1, id_tRNA_OPELVcst, 1, 3, 2, id_tRNA_SLVDLV, 
        6, 3, id_tRNA_CMPLVcst, 0, 6, -142857, 6, 
        id_tRNA_INCLV, 1, 6, id_tRNA_IF0, 6, id_tRNA_OPELVcst, 1, 
        3, 7, id_tRNA_INCLV, 0, 5, id_tRNA_SLVDLV, 6, 
        3, id_tRNA_CMPLVcst, 0, 6, -142857, 6, id_tRNA_INCLV, 
        1, 6, id_tRNA_SWJ, id_tRNA_SDLVLV, 3, 5, id_tRNA_RET, 
        GSTOP_ID, 0, 0, 0, 0, 0, 0,

        // tRNA_SEJ

        GSTART_ID, id_tRNA_SEJ, id_tRNA_CVARS, LV_place, 5, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_SLVDLV, 3, 2, id_tRNA_SLVcst, 4, 1, 
        id_tRNA_OPELVcst, 1, 3, 2, id_tRNA_SLVDLV, 5, 3, 
        id_tRNA_CMPLVcst, 0, 5, -285714, 5, id_tRNA_INCLV, 1, 
        5, id_tRNA_IF0, 5, id_tRNA_OPELVcst, 1, 3, 7, 
        id_tRNA_INCLV, 0, 4, id_tRNA_SLVDLV, 5, 3, id_tRNA_CMPLVcst, 
        0, 5, -285714, 5, id_tRNA_INCLV, 1, 5, 
        id_tRNA_SWJ, id_tRNA_SDLVLV, 3, 4, id_tRNA_RET, GSTOP_ID, 0, 

        // tRNA_SWJ

        GSTART_ID, id_tRNA_SWJ, id_tRNA_CVARS, LV_place, 6, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_SLVDLV, 3, 2, id_tRNA_SLVcst, 4, 1, 
        id_tRNA_OPELVcst, 1, 3, 2, id_tRNA_SLVDLV, 5, 3,
        id_tRNA_CMPLVcst, 0, 5, -142857, 5, id_tRNA_INCLV, 1, 
        5, id_tRNA_IF0, 5, id_tRNA_OPELVcst, 1, 3, 7, 
        id_tRNA_INCLV, 0, 4, id_tRNA_SLVDLV, 5, 3, id_tRNA_CMPLVcst, 
        0, 5, -142857, 5, id_tRNA_INCLV, 1, 5, 
        id_tRNA_SWJ, id_tRNA_SDLVLV, 3, 4, id_tRNA_INCDLV, 0, 3, 
        id_tRNA_MInstr, instruction::JRS, id_tRNA_M0, id_tRNA_M0, id_tRNA_M0, id_tRNA_INCDLV, 0, 
        2, id_tRNA_SLVDLV, 6, 2, id_tRNA_SDLVLV, 6, 4, 
        id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_JLV

        GSTART_ID, id_tRNA_JLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::JMP, id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, id_tRNA_MLV, 
        id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_SOScst

        GSTART_ID, id_tRNA_SOScst, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::SETOS, id_tRNA_M0, id_tRNA_M0, id_tRNA_M0, id_tRNA_Marg, 
        id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_SOSLV

        GSTART_ID, id_tRNA_SOSLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::SETOS, id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, id_tRNA_MLV, 
        id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_GISLV

        GSTART_ID, id_tRNA_GISLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::CPYIS, id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, id_tRNA_MLV, 
        id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_PCSI

        GSTART_ID, id_tRNA_PCSI, id_tRNA_CVARS, LV_place, 4, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::INC, id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 
        99, id_tRNA_M0, id_tRNA_M0, id_tRNA_MCPY, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_Mcst, 99, id_tRNA_Marg, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 

        // tRNA_PLVSI

        GSTART_ID, id_tRNA_PLVSI, id_tRNA_CVARS, LV_place, 4, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::INC, id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 
        99, id_tRNA_M0, id_tRNA_M0, id_tRNA_MCPY, id_tRNA_M2, id_tRNA_M1, id_tRNA_M0, 
        id_tRNA_Mcst, 99, id_tRNA_MLV, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 

        // tRNA_PCSWI

        GSTART_ID, id_tRNA_PCSWI, id_tRNA_CVARS, LV_place, 4, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MCPY, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 99, 
        id_tRNA_Marg, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_PLVSWI

        GSTART_ID, id_tRNA_PLVSWI, id_tRNA_CVARS, LV_place, 4, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MCPY, id_tRNA_M2, id_tRNA_M1, id_tRNA_M0, id_tRNA_Mcst, 99, 
        id_tRNA_MLV, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_CMPLVcst

        GSTART_ID, id_tRNA_CMPLVcst, id_tRNA_CVARS, LV_place, 4, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_SLVDLV, 3, 1, id_tRNA_SLVDLV, 3, 3, 
        id_tRNA_INCDLV, 0, 1, id_tRNA_CMPLVcst, 0, 3, 0, 
        4, id_tRNA_IF0, 4, id_tRNA_SLVcst, 3, instruction::JRE, id_tRNA_SIJ, 
        id_tRNA_CMPLVcst, 0, 3, 1, 4, id_tRNA_IF0, 4, 
        id_tRNA_SLVcst, 3, instruction::JRL, id_tRNA_SIJ, id_tRNA_CMPLVcst, 0, 3, 
        2, 4, id_tRNA_IF0, 4, id_tRNA_SLVcst, 3, instruction::JRG, 
        id_tRNA_SIJ, id_tRNA_CMPLVcst, 0, 3, 3, 4, id_tRNA_IF0, 
        4, id_tRNA_SLVcst, 3, instruction::JRLE, id_tRNA_SIJ, id_tRNA_SLVcst, 3, 
        instruction::JRGE, id_tRNA_SEJ, id_tRNA_SEJ, id_tRNA_SEJ, id_tRNA_SEJ, id_tRNA_INCDLV, 0, 
        2, id_tRNA_SLVDLV, 4, 2, id_tRNA_SDLVLV, 4, 3, 
        id_tRNA_M0, id_tRNA_M1, id_tRNA_M0, id_tRNA_M3, id_tRNA_MLV, id_tRNA_Marg, id_tRNA_MCPY, 
        id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, id_tRNA_MLV, id_tRNA_M0, id_tRNA_M0, id_tRNA_MInstr, 
        instruction::JRA, id_tRNA_M0, id_tRNA_M0, id_tRNA_M0, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_MCPY, id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, id_tRNA_MLVW, id_tRNA_M1, id_tRNA_M0, 
        id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0, 0, 

        // tRNA_CMPLVLV

        GSTART_ID, id_tRNA_CMPLVLV, id_tRNA_CVARS, LV_place, 4, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_SLVDLV, 3, 1, id_tRNA_SLVDLV, 3, 3, 
        id_tRNA_INCDLV, 0, 1, id_tRNA_CMPLVcst, 0, 3, 0, 
        4,id_tRNA_IF0, 4, id_tRNA_SLVcst, 3, instruction::JRE, id_tRNA_SIJ, 
        id_tRNA_CMPLVcst, 0, 3, 1, 4, id_tRNA_IF0, 4, 
        id_tRNA_SLVcst, 3, instruction::JRL, id_tRNA_SIJ, id_tRNA_CMPLVcst, 0, 3, 
        2, 4, id_tRNA_IF0, 4, id_tRNA_SLVcst, 3, instruction::JRG, 
        id_tRNA_SIJ, id_tRNA_CMPLVcst, 0, 3, 3, 4, id_tRNA_IF0, 
        4, id_tRNA_SLVcst, 3, instruction::JRLE, id_tRNA_SIJ, id_tRNA_SLVcst, 3, 
        instruction::JRGE, id_tRNA_SEJ, id_tRNA_SEJ, id_tRNA_SEJ, id_tRNA_SEJ, id_tRNA_INCDLV, 0, 
        2, id_tRNA_SLVDLV, 4, 2, id_tRNA_SDLVLV, 4, 3, 
        id_tRNA_M0, id_tRNA_M1, id_tRNA_M1, id_tRNA_M3, id_tRNA_MLV, id_tRNA_MLV, id_tRNA_MCPY, 
        id_tRNA_M1,id_tRNA_M0, id_tRNA_M0, id_tRNA_MLV, id_tRNA_M0, id_tRNA_M0, id_tRNA_MInstr, 
        instruction::JRA, id_tRNA_M0, id_tRNA_M0, id_tRNA_M0, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_MCPY, id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, id_tRNA_MLVW, id_tRNA_M1, id_tRNA_M0, 
        id_tRNA_RET,GSTOP_ID, 0, 0, 0, 0, 0, 

        // tRNA_OPEcstcst

        GSTART_ID, id_tRNA_OPEcstcst, id_tRNA_CVARS, LV_place, 4, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_SLVDLV, 3, 1, id_tRNA_SLVDLV, 3, 3, 
        id_tRNA_INCDLV, 0, 1, id_tRNA_CMPLVcst, 0, 3, 0, 
        4, id_tRNA_IF0, 4, id_tRNA_SLVcst, 3, instruction::ADD, id_tRNA_SIJ, 
        id_tRNA_CMPLVcst, 0, 3, 1, 4, id_tRNA_IF0, 4, 
        id_tRNA_SLVcst, 3, instruction::SUB, id_tRNA_SIJ, id_tRNA_CMPLVcst, 0, 3, 
        2, 4, id_tRNA_IF0, 4, id_tRNA_SLVcst, 3, instruction::MUL, 
        id_tRNA_SIJ, id_tRNA_SLVcst, 3, instruction::DIV, id_tRNA_SEJ, id_tRNA_SEJ, id_tRNA_SEJ, 
        id_tRNA_INCDLV, 0, 2, id_tRNA_SLVDLV, 4, 2, id_tRNA_SDLVLV, 
        4, 3, id_tRNA_M1, id_tRNA_M1, id_tRNA_M0, id_tRNA_MargW, id_tRNA_Marg, 
        id_tRNA_Marg, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0,

        // tRNA_OPEcstLV

        GSTART_ID, id_tRNA_OPEcstLV, id_tRNA_CVARS, LV_place, 4, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_SLVDLV, 3, 1, id_tRNA_SLVDLV, 3, 3, 
        id_tRNA_INCDLV, 0, 1, id_tRNA_CMPLVcst, 0, 3, 0, 
        4, id_tRNA_IF0, 4, id_tRNA_SLVcst, 3, instruction::ADD, id_tRNA_SIJ, 
        id_tRNA_CMPLVcst, 0, 3, 1, 4, id_tRNA_IF0, 4, 
        id_tRNA_SLVcst, 3, instruction::SUB, id_tRNA_SIJ, id_tRNA_CMPLVcst, 0, 3, 
        2, 4, id_tRNA_IF0, 4, id_tRNA_SLVcst, 3, instruction::MUL, 
        id_tRNA_SIJ, id_tRNA_SLVcst, 3, instruction::DIV, id_tRNA_SEJ, id_tRNA_SEJ, id_tRNA_SEJ, 
        id_tRNA_INCDLV, 0, 2, id_tRNA_SLVDLV, 4, 2, id_tRNA_SDLVLV, 
        4, 3, id_tRNA_M1, id_tRNA_M1, id_tRNA_M0, id_tRNA_MargW, id_tRNA_Marg, 
        id_tRNA_MLV, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0, 

        // tRNA_OPELVcst

        GSTART_ID, id_tRNA_OPELVcst, id_tRNA_CVARS, LV_place, 4, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_SLVDLV, 3, 1, id_tRNA_SLVDLV, 3, 3, 
        id_tRNA_INCDLV, 0, 1, id_tRNA_CMPLVcst, 0, 3, 0, 
        4,id_tRNA_IF0, 4, id_tRNA_SLVcst, 3, instruction::ADD, id_tRNA_SIJ, 
        id_tRNA_CMPLVcst, 0, 3, 1, 4, id_tRNA_IF0, 4, 
        id_tRNA_SLVcst, 3, instruction::SUB, id_tRNA_SIJ, id_tRNA_CMPLVcst, 0, 3, 
        2, 4, id_tRNA_IF0, 4, id_tRNA_SLVcst, 3, instruction::MUL, 
        id_tRNA_SIJ, id_tRNA_SLVcst, 3, instruction::DIV, id_tRNA_SEJ, id_tRNA_SEJ, id_tRNA_SEJ, 
        id_tRNA_INCDLV, 0, 2, id_tRNA_SLVDLV, 4, 2, id_tRNA_SDLVLV, 
        4, 3, id_tRNA_M1, id_tRNA_M1, id_tRNA_M0, id_tRNA_MLV, id_tRNA_MLVW, 
        id_tRNA_Marg, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0,

        // tRNA_OPELVLV

        GSTART_ID, id_tRNA_OPELVLV, id_tRNA_CVARS, LV_place, 4, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_SLVDLV, 3, 1, id_tRNA_SLVDLV, 3, 3, 
        id_tRNA_INCDLV, 0, 1, id_tRNA_CMPLVcst, 0, 3, 0, 
        4,id_tRNA_IF0, 4, id_tRNA_SLVcst, 3, instruction::ADD, id_tRNA_SIJ, 
        id_tRNA_CMPLVcst, 0, 3, 1, 4, id_tRNA_IF0, 4, 
        id_tRNA_SLVcst, 3, instruction::SUB, id_tRNA_SIJ, id_tRNA_CMPLVcst, 0, 3, 
        2, 4, id_tRNA_IF0, 4, id_tRNA_SLVcst, 3, instruction::MUL, 
        id_tRNA_SIJ, id_tRNA_SLVcst, 3, instruction::DIV, id_tRNA_SEJ, id_tRNA_SEJ, id_tRNA_SEJ, 
        id_tRNA_INCDLV, 0, 2, id_tRNA_SLVDLV, 4, 2, id_tRNA_SDLVLV, 
        4, 3, id_tRNA_M1, id_tRNA_M1, id_tRNA_M1, id_tRNA_MLV, id_tRNA_MLVW, 
        id_tRNA_MLV, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0,

        // tRNA_INCcst

        GSTART_ID, id_tRNA_INCcst, id_tRNA_CVARS, LV_place, 4, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_SLVDLV, 3, 1, id_tRNA_SLVDLV, 3, 3, 
        id_tRNA_INCDLV, 0, 1, id_tRNA_CMPLVcst, 0, 3, 0, 
        4, id_tRNA_IF0, 4, id_tRNA_SLVcst, 3, instruction::INC, id_tRNA_SIJ, 
        id_tRNA_SLVcst, 3, instruction::DEC, id_tRNA_SEJ, id_tRNA_INCDLV, 0, 2, 
        id_tRNA_SLVDLV, 4, 2, id_tRNA_SDLVLV, 4, 3, id_tRNA_M1, 
        id_tRNA_M0, id_tRNA_M0, id_tRNA_Marg, id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 

        // tRNA_INCLV

        GSTART_ID, id_tRNA_INCLV, id_tRNA_CVARS, LV_place, 4, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_SLVDLV, 3, 1, id_tRNA_SLVDLV, 3, 3, 
        id_tRNA_INCDLV, 0, 1, id_tRNA_CMPLVcst, 0, 3, 0, 
        4, id_tRNA_IF0, 4, id_tRNA_SLVcst, 3, instruction::INC, id_tRNA_SIJ, 
        id_tRNA_SLVcst, 3, instruction::DEC, id_tRNA_SEJ, id_tRNA_INCDLV, 0, 2, 
        id_tRNA_SLVDLV, 4, 2, id_tRNA_SDLVLV, 4, 3, id_tRNA_M1, 
        id_tRNA_M0, id_tRNA_M0, id_tRNA_MLV, id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 

        // tRNA_INCDLV

        GSTART_ID, id_tRNA_INCDLV, id_tRNA_CVARS, LV_place, 4, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_SLVDLV, 3, 1, id_tRNA_SLVDLV, 3, 3, 
        id_tRNA_INCDLV, 0, 1, id_tRNA_CMPLVcst, 0, 3, 0, 
        4, id_tRNA_IF0, 4, id_tRNA_SLVcst, 3, instruction::INC, id_tRNA_SIJ, 
        id_tRNA_SLVcst, 3, instruction::DEC, id_tRNA_SEJ, id_tRNA_INCDLV, 0, 2, 
        id_tRNA_SLVDLV, 4, 2, id_tRNA_SDLVLV, 4, 3, id_tRNA_M2, 
        id_tRNA_M0, id_tRNA_M0, id_tRNA_MLV, id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 

        // tRNA_INCS

        GSTART_ID, id_tRNA_INCS, id_tRNA_CVARS, LV_place, 4, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_SLVDLV, 3, 1, id_tRNA_SLVDLV, 3, 3, 
        id_tRNA_INCDLV, 0, 1, id_tRNA_CMPLVcst, 0, 3, 0, 
        4, id_tRNA_IF0, 4, id_tRNA_SLVcst, 3, instruction::INC, id_tRNA_SIJ, 
        id_tRNA_SLVcst, 3, instruction::DEC, id_tRNA_SEJ, id_tRNA_INCDLV, 0, 2, 
        id_tRNA_SLVDLV, 4, 2, id_tRNA_SDLVLV, 4, 3, id_tRNA_M2, 
        id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 99, id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, 
        GSTOP_ID, 0, 0, 0, 0, 0, 0,

        // tRNA_CALLcst

        GSTART_ID, id_tRNA_CALLcst, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::CALL, id_tRNA_M0, id_tRNA_M0, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_Marg, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_CALLLV

        GSTART_ID, id_tRNA_CALLLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::CALL, id_tRNA_M0, id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_MLV, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 


        // tRNA_RUIcstcst

        GSTART_ID, id_tRNA_RUIcstcst, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::RUI, id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, id_tRNA_MLV, 
        id_tRNA_Marg, id_tRNA_Marg, id_tRNA_RET, GSTOP_ID, 0, 0, 0,


        // tRNA_RUIcstLV

        GSTART_ID, id_tRNA_RUIcstLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::RUI, id_tRNA_M1, id_tRNA_M0, id_tRNA_M1, id_tRNA_MLV, 
        id_tRNA_Marg, id_tRNA_MLV, id_tRNA_RET, GSTOP_ID, 0, 0, 0,


        // tRNA_RUILVcst

        GSTART_ID, id_tRNA_RUILVcst, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::RUI, id_tRNA_M1, id_tRNA_M1, id_tRNA_M0, id_tRNA_MLV, 
        id_tRNA_MLV, id_tRNA_Marg, id_tRNA_RET, GSTOP_ID, 0, 0, 0,


        // tRNA_RUILVLV

        GSTART_ID, id_tRNA_RUILVLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::RUI, id_tRNA_M1, id_tRNA_M1, id_tRNA_M1, id_tRNA_MLV, 
        id_tRNA_MLV, id_tRNA_MLV, id_tRNA_RET, GSTOP_ID, 0, 0, 0,


        // tRNA_GScstcst

        GSTART_ID, id_tRNA_GScstcst, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::GSET, id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, id_tRNA_Marg, 
        id_tRNA_Marg, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_GScstLV

        GSTART_ID, id_tRNA_GScstLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::GSET, id_tRNA_M1, id_tRNA_M1, id_tRNA_M0, id_tRNA_Marg, 
        id_tRNA_MLV, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_GSLVcst

        GSTART_ID, id_tRNA_GSLVcst, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::GSET, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, id_tRNA_MLV, 
        id_tRNA_Marg, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_GSLVLV

        GSTART_ID, id_tRNA_GSLVLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::GSET, id_tRNA_M2, id_tRNA_M1, id_tRNA_M0, id_tRNA_MLV, 
        id_tRNA_MLV, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_USLV

        GSTART_ID, id_tRNA_USLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::CPYUS, id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, id_tRNA_MLV, 
        id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_RULV

        GSTART_ID, id_tRNA_RULV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::READ, id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, id_tRNA_MLV, 
        id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_EMPTY

        GSTART_ID, id_tRNA_EMPTY, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::EMPTY, id_tRNA_M1, id_tRNA_M1, id_tRNA_M0, id_tRNA_MLV, 
        id_tRNA_MLV, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_WRITE

        GSTART_ID, id_tRNA_WRITE, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::WRITE, id_tRNA_M1, id_tRNA_M1, id_tRNA_M0, id_tRNA_MLV, 
        id_tRNA_MLV, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_HALT

        GSTART_ID, id_tRNA_HALT, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::HALT, id_tRNA_M0, id_tRNA_M0, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 


        // tRNA_MP

        GSTART_ID, id_tRNA_MP, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MCPY, id_tRNA_M1, id_tRNA_M1, id_tRNA_M0, id_tRNA_Mcst, 100, 
        id_tRNA_Mcst, 99, id_tRNA_M0, id_tRNA_MInstr, instruction::INC, id_tRNA_M2, id_tRNA_M0, 
        id_tRNA_M0, id_tRNA_Mcst, 100, id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 

        // tRNA_ME

        GSTART_ID, id_tRNA_ME, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::DEC, id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 
        99, id_tRNA_M0, id_tRNA_M0, id_tRNA_MCPY, id_tRNA_M1, id_tRNA_M2, id_tRNA_M0, 
        id_tRNA_Mcst, 101, id_tRNA_Mcst, 99, id_tRNA_M0, id_tRNA_MInstr, instruction::INC, 
        id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 99, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_MInstr, instruction::INC, id_tRNA_M1, id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 101, 
        id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_Mcst

        GSTART_ID, id_tRNA_Mcst, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::INC, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 
        101, id_tRNA_M0, id_tRNA_M0, id_tRNA_MCPY, id_tRNA_M3, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_Mcst, 101, id_tRNA_Marg, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 

        // tRNA_M0

        GSTART_ID, id_tRNA_M0, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::INC, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 
        101, id_tRNA_M0, id_tRNA_M0, id_tRNA_MCPY, id_tRNA_M3, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_Mcst, 101, id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 

        // tRNA_M1

        GSTART_ID, id_tRNA_M1, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::INC, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 
        101, id_tRNA_M0, id_tRNA_M0, id_tRNA_MCPY, id_tRNA_M3, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_Mcst, 101, id_tRNA_M1, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 

        // tRNA_M2

        GSTART_ID, id_tRNA_M2, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::INC, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 
        101, id_tRNA_M0, id_tRNA_M0, id_tRNA_MCPY, id_tRNA_M3, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_Mcst, 101, id_tRNA_M2, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 

        // tRNA_M3

        GSTART_ID, id_tRNA_M3, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::INC, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 
        101, id_tRNA_M0, id_tRNA_M0, id_tRNA_MCPY, id_tRNA_M3, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_Mcst,101, id_tRNA_M3, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 

        // tRNA_MInstr

        GSTART_ID, id_tRNA_MInstr, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::INC, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 
        101, id_tRNA_M0, id_tRNA_M0, id_tRNA_MCPY, id_tRNA_M3, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_Mcst, 101, id_tRNA_Marg, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 

        // tRNA_MCPY

        GSTART_ID, id_tRNA_MCPY, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::INC, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 
        101, id_tRNA_M0, id_tRNA_M0, id_tRNA_MCPY, id_tRNA_M3, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_Mcst, 101, id_tRNA_MCPY, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 

        // tRNA_Marg

        GSTART_ID, id_tRNA_Marg, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::INC, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 
        101, id_tRNA_M0, id_tRNA_M0, id_tRNA_MCPY, id_tRNA_M3, id_tRNA_M3, id_tRNA_M0, 
        id_tRNA_Mcst, 101, id_tRNA_Mcst, 100, id_tRNA_M0, id_tRNA_MInstr, instruction::INC, 
        id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 100, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0, 0, 

        // tRNA_MargW

        GSTART_ID, id_tRNA_MargW, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::INC, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 
        101, id_tRNA_M0, id_tRNA_M0, id_tRNA_MCPY, id_tRNA_M3, id_tRNA_M3, id_tRNA_M0, 
        id_tRNA_Mcst, 101, id_tRNA_Mcst, 100, id_tRNA_M0, id_tRNA_RET, GSTOP_ID,

        // tRNA_MLV

        GSTART_ID, id_tRNA_MLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::INC, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 
        101, id_tRNA_M0, id_tRNA_M0, id_tRNA_MInstr, instruction::ADD, id_tRNA_M1, id_tRNA_M1, 
        id_tRNA_M3, id_tRNA_Mcst, 103, id_tRNA_Mcst, 98, id_tRNA_Mcst, 100, 
        id_tRNA_MCPY, id_tRNA_M3, id_tRNA_M2, id_tRNA_M0, id_tRNA_Mcst, 101, id_tRNA_Mcst, 
        103, id_tRNA_M0, id_tRNA_MInstr, instruction::INC, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_Mcst, 100, id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 

        // tRNA_MLVW

        GSTART_ID, id_tRNA_MLVW, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::INC, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, id_tRNA_Mcst, 
        101, id_tRNA_M0, id_tRNA_M0, id_tRNA_MCPY, id_tRNA_M3, id_tRNA_M2, id_tRNA_M0,
        id_tRNA_Mcst, 101, id_tRNA_Mcst, 103, id_tRNA_M0, id_tRNA_RET, GSTOP_ID,

        // tRNA_SP_GPTR

        GSTART_ID, id_tRNA_SP_GPTR, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::GPTR, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_SP_FCTADD

        GSTART_ID, id_tRNA_SP_FCTADD, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::ADD, id_tRNA_M2, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_M0, id_tRNA_M3, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_SP_GFPTRLV

        GSTART_ID, id_tRNA_SP_GFPTRLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MCPY, id_tRNA_M1, id_tRNA_M2, id_tRNA_M0, id_tRNA_MLV, id_tRNA_M0, 
        id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 0, 

        // tRNA_SP_GSPLV

        GSTART_ID, id_tRNA_SP_GSPLV, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MCPY, id_tRNA_M1, id_tRNA_M1, id_tRNA_M0, id_tRNA_MLV, id_tRNA_Mcst, 
        99, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_SP_GCPY

        GSTART_ID, id_tRNA_SP_GCPY, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::GCPY, id_tRNA_M2, id_tRNA_M2, id_tRNA_M2, id_tRNA_MLV, 
        id_tRNA_MLV, id_tRNA_MLV, id_tRNA_RET, GSTOP_ID, 0, 0, 0, 

        // tRNA_RET

        GSTART_ID, id_tRNA_RET, id_tRNA_CVARS, LV_place, 3, id_tRNA_IVARS, id_tRNA_MP, 
        id_tRNA_ME, id_tRNA_MInstr, instruction::JMP, id_tRNA_M2, id_tRNA_M0, id_tRNA_M0, id_tRNA_M0, 
        id_tRNA_M0, id_tRNA_M0, id_tRNA_RET, GSTOP_ID, 0, 0, 0,


        // 1 - main func

        GSTART_ID, 1, id_tRNA_CVARS, LV_place, 0, id_tRNA_IVARS, id_tRNA_SOScst,
        0, id_tRNA_CALLcst, id_core_switcher, id_tRNA_HALT, id_tRNA_RET, GSTOP_ID, 0,

        
        // 0 - func executor

        GSTART_ID, 0, id_tRNA_CVARS, LV_place, 5, id_tRNA_IVARS, id_tRNA_GTSLV,
        1, id_tRNA_SLVcst, 2, 0, id_tRNA_SLVcst, 3, 1,
        id_tRNA_IF0, 3, id_tRNA_OPELVcst, 0, 2, 7, id_tRNA_RGLVLV,
        4, 2, id_tRNA_CMPLVcst, 0, 4, instruction::MARKER, 3,
        id_tRNA_IF0, 3, id_tRNA_OPELVcst, 0, 2, 2, id_tRNA_RGLVLV,
        4, 2, id_tRNA_CMPLVLV, 0, 4, 1, 3, 
        id_tRNA_OPELVcst, 1, 3, 1, id_tRNA_OPELVcst, 1, 2, 
        2, id_tRNA_SIJ, id_tRNA_SLVcst, 3, 1, id_tRNA_SEJ, id_tRNA_SWJ, 
        id_tRNA_INCcst, 1, 99, id_tRNA_OPELVcst, 3, 2, 7, 
        id_tRNA_INCcst, 0, 0, id_tRNA_SP_GPTR, id_tRNA_SP_FCTADD, id_tRNA_JLV, 2, 
        id_tRNA_INCcst, 1, 0, id_tRNA_SP_GFPTRLV, 5, id_tRNA_INCcst, 1, 
        0, id_tRNA_JLV, 5, GSTOP_ID, 0, 0, 0
    };

    return DNA;
}

void SelfCompilationEvoX::exec_step_1(sp_univ_evo_algos universe, sp_evox algo)
{
    //----- get DNA as free molecules

    std::vector<int> DNA = get_DNA_step_1();

    sp_free_molecules free_molecules = std::make_shared<FreeMolecules>("free molecules");
    free_molecules->init();
    free_molecules->set_phenotypic_body(DNA);
    universe->get_places()[1]->set_entity(free_molecules);

    algo->set_input({3, -1}); // inject DNA as free molecules with ID -1
    universe->exec();

    write_phenotypic_body_to_csv(algo->get_phenotypic_body(), "phenotypic_body_with_bootstrap_DNA.csv");
}

void SelfCompilationEvoX::build_new_algo_artificially(sp_evox base_algo, std::string file_name)
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

void SelfCompilationEvoX::exec_step_2(sp_univ_evo_algos universe, sp_evox algo)
{
    // transcribe DNA only functions
    // self compilation functions
    algo->set_input({-1, id_transcriber, id_self_compil_func_ID_list});
    universe->exec();
    algo->set_input({-1, id_transcriber, id_self_compil_transcription});
    universe->exec();
    // some remaining tRNAs
    algo->set_input({-1, id_transcriber, id_tRNA_GADD});
    universe->exec();
    // aggregators and mutators
    algo->set_input({-1, id_transcriber, id_mRNA_meta_aggregator});
    universe->exec();
    algo->set_input({-1, id_transcriber, id_DNA_metamutator});
    universe->exec();
    // other functions
    algo->set_input({-1, id_transcriber, id_DNA_checker}); // func in DNA check
    universe->exec();
    algo->set_input({-1, id_transcriber, id_DNA_pos}); // DNA pos
    universe->exec();

    write_phenotypic_body_to_csv(algo->get_phenotypic_body(), "phenotypic_body_with_bootstrap_DNA_full.csv");
    // apply the self compilation functions
    algo->set_input({-1, id_self_compil_func_ID_list});
    universe->exec();

    algo->debug_ribosome = true;
    for(int i=0;i<nb_genes;i++)
    {
        algo->set_input({-1, id_self_compil_transcription});
        universe->exec();
    }

    algo->set_input({-1, id_self_compil_transcription});
    universe->exec();

    // algo must have replicated at place 1
    int expected_place = 1;
    sp_entity entity = universe->get_places()[expected_place]->get_entity();
    sp_evox transcribed_algo = std::dynamic_pointer_cast<EvoX>(entity);

    if(transcribed_algo != nullptr)
    {
        std::cout << "Algo transcribed !" << std::endl;
        std::vector<int> phenotypic_body = transcribed_algo->get_phenotypic_body();
        write_phenotypic_body_to_csv(phenotypic_body, "phenotypic_body_transcribed.csv");
    }
    else
    {
        std::cout << "Failed ! place " << expected_place
                  <<" doesn't contain an EvoX algo..." 
                  << std::endl;

    }
}

void SelfCompilationEvoX::exec_step_3(sp_univ_evo_algos universe, sp_evox algo)
{
    // apply the self compilation functions
    algo->set_input({-1, id_self_compil_func_ID_list});
    universe->exec();

    for(int i=0;i<nb_genes;i++)
    {
        algo->set_input({});
        universe->exec();
    }

    algo->set_input({});
    universe->exec();

    // algo must have replicated at place 2
    int expected_place = 2;
    sp_entity entity = universe->get_places()[expected_place]->get_entity();
    sp_evox transcribed_algo = std::dynamic_pointer_cast<EvoX>(entity);

    if(transcribed_algo != nullptr)
    {
        std::cout << "Algo transcribed !" << std::endl;
        std::vector<int> phenotypic_body = transcribed_algo->get_phenotypic_body();
        write_phenotypic_body_to_csv(phenotypic_body, "phenotypic_body_transcribed_iterated.csv");
    }
    else
    {
        std::cout << "Failed ! place " << expected_place
                  <<" doesn't contain an EvoX algo..." 
                  << std::endl;
    }
}
