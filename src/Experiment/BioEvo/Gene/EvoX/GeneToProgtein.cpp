#include "GeneToProgtein.hpp"

#include <fstream>

#include "../../../../Utils/Functions.hpp"
#include "../../../../Utils/Maths/RandomGen.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/FreeMolecules.hpp"


/**
 * Teleonomical IDs of interpretation proteins :
 *  - 10000 : INIT, init
 *  - 10100 : NLV, new local var
 *  - 10200 : GILV, get input in local var
 * 
*/


GeneToProgtein::GeneToProgtein()
    :Experiment::Experiment(name_exp_bioevo_molecular_body_evox_gtp)
{
    init();
}

void GeneToProgtein::init()
{
    heaviside_threshold = 21;
}

void GeneToProgtein::launch()
{
    sp_evox algo = get_base_algo();
    sp_univ_evo_algos univ = get_universe(algo);

    exec_step_1(univ, algo);
    exec_step_2(univ, algo);
    exec_step_3(univ, algo);
    exec_step_4(univ, algo);

    std::cout << "Experiment over" << std::endl;
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
    algo->set_max_nb_instr_exec(80000);
    // get molecular body from csv
    std::vector<int> molecular_body = get_molecular_body_from_csv("molecular_body_base_algo_1.csv");
    algo->set_molecular_body(molecular_body);

    // set data stack at 150
    algo->set_data_at(99, 150);

    return algo;
}

//-------------------- step 1

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
        instruction::MOV, 2, 1, 0, 99, 101, 0,
        // end of func
        instruction::JMP, 2, 0, 0, 0, 0, 0};

    return heaviside;
}

void GeneToProgtein::exec_step_1(sp_univ_evo_algos universe, sp_evox algo)
{
    //----- get Heaviside function

    std::vector<int> heaviside = get_heaviside();

    sp_free_molecules free_molecules = std::make_shared<FreeMolecules>("free molecules");
    free_molecules->init();
    free_molecules->set_molecular_body(heaviside);
    universe->get_places()[1]->set_entity(free_molecules);

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

//-------------------- step 2

std::map<std::string, std::vector<int>> GeneToProgtein::get_tRNAs_1() 
{
    // note :
    // ribosome increments stack before calling so that
    // we can add fct ID on stack for meta exec
    // --> stack should be pointing to ribosome ptr initially

    // create n vars
    std::vector<int> tRNA_CVARS {
        3, id_tRNA_CVARS,

        // 2 args : position of var heap and nb of vars
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // set heap pos and increment ribosome ptr
        instruction::CPY, 1, 3, 0, 98, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // set heap size = n and increment ribosome ptr
        instruction::CPY, 2, 3, 0, 98, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // init vars
    std::vector<int> tRNA_IVARS {
        3, id_tRNA_IVARS,

        // 0 arg
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // set vars names
        instruction::CPY, 1, 1, 0, 101, 98, 0, // var nb ptr
        instruction::CPY, 1, 1, 0, 102, 101, 0, // var nb end
        instruction::ADD, 1, 1, 2, 102, 102, 98,
        instruction::CPY, 1, 0, 0, 103, 100, 0, // var name
        instruction::JRGE, 0, 1, 1, 5, 101, 102,
        instruction::INC, 1, 0, 0, 101, 0, 0,
        instruction::CPY, 2, 1, 0, 101, 103, 0,
        instruction::INC, 1, 0, 0, 103, 0, 0,
        instruction::JRS, 0, 0, 0, 4, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // set local var (const)
    std::vector<int> tRNA_SLVcst {
        3, id_tRNA_SLVcst,
        
        // 2 args : var nb, arg val (const) 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // CPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // cst val
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // set dereferenced local var (const)
    std::vector<int> tRNA_SDLVcst {
        3, id_tRNA_SDLVcst,
        
        // 2 args : var nb, arg val (const) 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // CPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // cst val
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // set local var with local var
    std::vector<int> tRNA_SLVLV {
        3, id_tRNA_SLVLV,
        
        // 2 args : var nb, var nb 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // CPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // set dereferenced local var (local var)
    std::vector<int> tRNA_SDLVLV {
        3, id_tRNA_SDLVLV,
        
        // 2 args : var nb, var nb 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // CPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // set local var (dereferenced local var)
    std::vector<int> tRNA_SLVDLV {
        3, id_tRNA_SLVDLV,
        
        // 2 args : var nb, var nb 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // CPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // set dereferenced local var (dereferenced local var)
    std::vector<int> tRNA_SDLVDLV {
        3, id_tRNA_SDLVDLV,
        
        // 2 args : arg nb, arg nb 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // CPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // set const addr with LV
    std::vector<int> tRNA_ScstLV {
        3, id_tRNA_ScstLV,
        
        // 2 args : addr, var nb
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // CPY 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // addr
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,     // arg0 : addr
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg1 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // set LV with val at cst address
    std::vector<int> tRNA_SLVaddr {
        3, id_tRNA_SLVaddr,
        
        // 2 args : var nb, addr
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // CPY 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg0 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // addr
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,     // arg1 : addr
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        instruction::JMP, 2, 0, 0, 0, 0, 0
    };



    // read gene at local var in local var
    std::vector<int> tRNA_RGLVLV {
        3, id_tRNA_RGLVLV,
        
        // 2 args : var nb 1, var nb 2 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // GR
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::GR, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // local var 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // write genes at dereferenced vars
    std::vector<int> tRNA_WGDLV {
        3, id_tRNA_WGDLV,
        
        // 3 args : var nb 1, var nb 2, var nb 3
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // GCPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::GCPY, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // local var 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // local var 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // local var 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };


    // get input into local variable
    std::vector<int> tRNA_GILV {
        3, id_tRNA_GILV,

        // 2 args : var nb and index in input
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // CPYIN
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPYIN, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // input index
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // get dereferenced input into local variable
    std::vector<int> tRNA_GDILV {
        3, id_tRNA_GDILV,

        // 2 args : var nb and index in input
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // CPYIN
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPYIN, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // input index
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // get input into dereferenced local variable
    std::vector<int> tRNA_GIDLV {
        3, id_tRNA_GIDLV,

        // 2 args : var nb and index in input
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101
        // put codons on stack
        // CPYIN
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPYIN, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // input index
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // get dereferenced input into dereferenced local variable
    std::vector<int> tRNA_GDIDLV {
        3, id_tRNA_GDIDLV,

        // 2 args : var nb and index in input
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101
        // put codons on stack
        // CPYIN
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPYIN, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // input index
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // get top of stack into local variable
    std::vector<int> tRNA_GTSLV {
        3, id_tRNA_GTSLV,

        // 1 args : var nb
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // CPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 99
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 99, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // get top of stack into local variable with decrement
    std::vector<int> tRNA_GTSLVD {
        3, id_tRNA_GTSLVD,

        // 1 args : var nb
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // CPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 99
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 99, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        // DEC
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::DEC, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 99
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 99, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // get top of stack into dereferenced local variable
    std::vector<int> tRNA_GTSDLV {
        3, id_tRNA_GTSDLV,

        // 1 args : var nb
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // CPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 99
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 99, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };


    // get local var into output
    std::vector<int> tRNA_GLVO {
        3, id_tRNA_GLVO,

        // 2 args : index in output and var nb
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // CPYOUT
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPYOUT, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // output index
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // if 
    /// jump if equals 0
    std::vector<int> tRNA_IF0 {
        3, id_tRNA_IF0,
        
        // 1 arg : var nb 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // JMP IF EQL
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::JRE, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // JUMP SIZE
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, -142857, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // size of if jump 
    /// builds the if jumps size
    std::vector<int> tRNA_SIJ {
        3, id_tRNA_SIJ,
        
        // 0 arg 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // JRA
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::JRA, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // JUMP SIZE
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, -285714, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        // set IF jump size
        instruction::CPY, 1, 2, 0, 102, 101, 0, // mobile subunit ptr
        instruction::CPY, 1, 0, 0, 103, 1, 0, // jump size
        instruction::SUB, 1, 1, 0, 102, 102, 2, // because we seek -142857 in first instr arg val
        // look for -142857 in first instr arg val of already written in protein
        instruction::JRE, 0, 2, 0, 4, 102, -142857,
        instruction::SUB, 1, 1, 0, 102, 102, 7, // move one instruction below
        instruction::INC, 1, 0, 0, 103, 0, 0,   // increase jump size
        instruction::JRS, 0, 0, 0, 3, 0, 0, 
        instruction::CPY, 2, 1, 0, 102, 103, 0, // set jump size

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // size of else jump 
    /// builds the if jumps size
    std::vector<int> tRNA_SEJ {
        3, id_tRNA_SEJ,
        
        // 0 arg 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // set ELSE jump size
        instruction::CPY, 1, 2, 0, 102, 101, 0, // mobile subunit ptr
        instruction::CPY, 1, 0, 0, 103, 1, 0, // jump size
        instruction::SUB, 1, 1, 0, 102, 102, 2, // because we seek -285714 in first instr arg val
        // look for -285714 in first instr arg val of already written in protein
        instruction::JRE, 0, 2, 0, 4, 102, -285714,
        instruction::SUB, 1, 1, 0, 102, 102, 7, // move one instruction below
        instruction::INC, 1, 0, 0, 103, 0, 0,   // increase jump size
        instruction::JRS, 0, 0, 0, 3, 0, 0, 
        instruction::CPY, 2, 1, 0, 102, 103, 0, // set jump size

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // while
    /// to use with IF
    std::vector<int> tRNA_SWJ {
        3, id_tRNA_SWJ,
        
        // 1 arg : var nb 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // set WHILE jump size
        instruction::CPY, 1, 2, 0, 102, 101, 0, // mobile subunit ptr
        instruction::CPY, 1, 0, 0, 103, 1, 0, // jump size
        instruction::SUB, 1, 1, 0, 102, 102, 2, // because we seek -142857 in first instr arg val
        // look for -142857 in first instr arg val of already written in protein
        instruction::JRE, 0, 2, 0, 4, 102, -142857,
        instruction::SUB, 1, 1, 0, 102, 102, 7, // move one instruction below
        instruction::INC, 1, 0, 0, 103, 0, 0,   // increase jump size
        instruction::JRS, 0, 0, 0, 3, 0, 0, 
        instruction::CPY, 2, 1, 0, 102, 103, 0, // set jump size
        instruction::INC, 2, 0, 0, 102, 0, 0,   // increase jump size to avoid fencepost error


        // put codons on stack
        // JMP IF EQL
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::JRS, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // JUMP SIZE
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 1, 0, 101, 103, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // jump
    /// jump at val at local var
    std::vector<int> tRNA_JLV {
        3, id_tRNA_JLV,
        
        // 1 args : local var nb
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // JMP 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 1, 0, 101, instruction::JMP, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg0 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };


    // set output size (cst)
    std::vector<int> tRNA_SOScst {
        3, id_tRNA_SOScst,
        
        // 1 arg : cst 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // SETOS
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::SETOS, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // cst output size
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // set output size (LV)
    std::vector<int> tRNA_SOSLV {
        3, id_tRNA_SOSLV,
        
        // 1 arg : var nb 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // SETOS
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::SETOS, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // get input size (local var)
    std::vector<int> tRNA_GISLV {
        3, id_tRNA_GISLV,
        
        // 1 arg : local var 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // CPYIS
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPYIS, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg0 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // put const on stack with increment
    std::vector<int> tRNA_PCSI {
        3, id_tRNA_PCSI,
        
        // 1 arg : cst val 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // 1 - increment stack
        // INC
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::INC, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 99
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 99, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        // 2 - put val on stack
        // CPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 99
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 99, 0,
        // cst
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // put local var on stack with increment
    std::vector<int> tRNA_PLVSI {
        3, id_tRNA_PLVSI,
        
        // 1 arg : var nb 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // 1 - increment stack
        // INC
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::INC, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 99
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 99, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        // 2 - put var on stack
        // CPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 99
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 99, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // put const on stack without increment
    std::vector<int> tRNA_PCSWI {
        3, id_tRNA_PCSWI,
        
        // 1 arg : cst val 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // CPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 99
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 99, 0,
        // cst
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // put local var on stack without increment
    std::vector<int> tRNA_PLVSWI {
        3, id_tRNA_PLVSWI,
        
        // 1 arg : var nb 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // CPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 99
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 99, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // CMP local var with cst
    std::vector<int> tRNA_CMPLVcst {
        3, id_tRNA_CMPLVcst,
        
        // 4 args : CMP OP, var nb, cst val, res var nb
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // get CMP OP
        instruction::CPY, 1, 3, 0, 102, 100, 0,     // arg0 : CMP OP
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // transcribe the CMP OP : 
        // 0 : ==
        // 1 : <
        // 2 : >
        // 3 : <=
        // else : >= 
        instruction::JRE, 0, 1, 0, 6, 102, 0,
        instruction::JRE, 0, 1, 0, 7, 102, 1,
        instruction::JRE, 0, 1, 0, 8, 102, 2,
        instruction::JRE, 0, 1, 0, 9, 102, 3,
        instruction::CPY, 1, 0, 0, 102, instruction::JRGE, 0,
        instruction::JRA, 0, 0, 0, 8, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::JRE, 0,
        instruction::JRA, 0, 0, 0, 6, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::JRL, 0,
        instruction::JRA, 0, 0, 0, 4, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::JRG, 0,
        instruction::JRA, 0, 0, 0, 2, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::JRLE, 0,

        // put codons on stack

        // 1 - JMP for LV CMP cst
        // JMP OP 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 1, 0, 101, 102, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg1 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // cst
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,     // arg2 : cst
        instruction::INC, 2, 0, 0, 100, 0, 0,

        // 2 - res <- 0
        // CPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg3 : res nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        // 3 - JRA 2
        // JRA
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::JRA, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        // 4 - res <- 1
        // CPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 2, 0, 101, 103, 0,     // arg3 in 103 : res nb
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // CMP local var with local var
    std::vector<int> tRNA_CMPLVLV {
        3, id_tRNA_CMPLVLV,
        
        // 4 args : CMP OP, var nb, var nb, res var nb
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // get CMP OP
        instruction::CPY, 1, 3, 0, 102, 100, 0,     // arg0 : CMP OP
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // transcribe the CMP OP : 
        // 0 : ==
        // 1 : <
        // 2 : >
        // 3 : <=
        // else : >= 
        instruction::JRE, 0, 1, 0, 6, 102, 0,
        instruction::JRE, 0, 1, 0, 7, 102, 1,
        instruction::JRE, 0, 1, 0, 8, 102, 2,
        instruction::JRE, 0, 1, 0, 9, 102, 3,
        instruction::CPY, 1, 0, 0, 102, instruction::JRGE, 0,
        instruction::JRA, 0, 0, 0, 8, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::JRE, 0,
        instruction::JRA, 0, 0, 0, 6, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::JRL, 0,
        instruction::JRA, 0, 0, 0, 4, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::JRG, 0,
        instruction::JRA, 0, 0, 0, 2, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::JRLE, 0,

        // put codons on stack

        // 1 - JMP for LV CMP cst
        // JMP OP 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 1, 0, 101, 102, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
        // local var 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg1 : var nb 1
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // local var 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg2 : var nb 2
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,

        // 2 - res <- 0
        // CPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg3 : res nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        // 3 - JRA 2
        // JRA
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::JRA, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        // 4 - res <- 1
        // CPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 2, 0, 101, 103, 0,     // arg3 in 103 : res nb
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // op-equal cst (cst addr += c or -=, *=,/=)
    std::vector<int> tRNA_OPEcstcst {
        3, id_tRNA_OPEcstcst,
        
        // 3 args : OP, var nb, cst val
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // get OP
        instruction::CPY, 1, 3, 0, 102, 100, 0,     // arg0 : OP
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // transcribe the OP : 
        // 0 : +=
        // 1 : -=
        // 2 : *=
        // else : /= 
        instruction::JRE, 0, 1, 0, 5, 102, 0,
        instruction::JRE, 0, 1, 0, 6, 102, 1,
        instruction::JRE, 0, 1, 0, 7, 102, 2,
        instruction::CPY, 1, 0, 0, 102, instruction::DIV, 0,
        instruction::JRA, 0, 0, 0, 6, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::ADD, 0,
        instruction::JRA, 0, 0, 0, 4, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::SUB, 0,
        instruction::JRA, 0, 0, 0, 2, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::MUL, 0,

        // put codons on stack

        // OP 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 1, 0, 101, 102, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // cst
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,     // arg1 : cst
        // cst
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,     // arg1 : cst
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // cst
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,     // arg2 : cst
        instruction::INC, 2, 0, 0, 100, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // op-equal cst (cst addr += LV or -=, *=,/=)
    std::vector<int> tRNA_OPEcstLV {
        3, id_tRNA_OPEcstLV,
        
        // 3 args : OP, var nb, cst val
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // get OP
        instruction::CPY, 1, 3, 0, 102, 100, 0,     // arg0 : OP
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // transcribe the OP : 
        // 0 : +=
        // 1 : -=
        // 2 : *=
        // else : /= 
        instruction::JRE, 0, 1, 0, 5, 102, 0,
        instruction::JRE, 0, 1, 0, 6, 102, 1,
        instruction::JRE, 0, 1, 0, 7, 102, 2,
        instruction::CPY, 1, 0, 0, 102, instruction::DIV, 0,
        instruction::JRA, 0, 0, 0, 6, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::ADD, 0,
        instruction::JRA, 0, 0, 0, 4, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::SUB, 0,
        instruction::JRA, 0, 0, 0, 2, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::MUL, 0,

        // put codons on stack

        // OP 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 1, 0, 101, 102, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // cst
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,     // arg1 : cst
        // cst
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,     // arg1 : cst
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg2 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,


        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // op-equal cst (x += c or -=, *=,/=)
    std::vector<int> tRNA_OPELVcst {
        3, id_tRNA_OPELVcst,
        
        // 3 args : OP, var nb, cst val
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // get OP
        instruction::CPY, 1, 3, 0, 102, 100, 0,     // arg0 : OP
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // transcribe the OP : 
        // 0 : +=
        // 1 : -=
        // 2 : *=
        // else : /= 
        instruction::JRE, 0, 1, 0, 5, 102, 0,
        instruction::JRE, 0, 1, 0, 6, 102, 1,
        instruction::JRE, 0, 1, 0, 7, 102, 2,
        instruction::CPY, 1, 0, 0, 102, instruction::DIV, 0,
        instruction::JRA, 0, 0, 0, 6, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::ADD, 0,
        instruction::JRA, 0, 0, 0, 4, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::SUB, 0,
        instruction::JRA, 0, 0, 0, 2, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::MUL, 0,

        // put codons on stack

        // OP 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 1, 0, 101, 102, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg1 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg1 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // cst
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,     // arg2 : cst
        instruction::INC, 2, 0, 0, 100, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // op-equal var (x += c or -=, *=,/=)
    std::vector<int> tRNA_OPELVLV {
        3, id_tRNA_OPELVLV,
        
        // 3 args : OP, var nb, var nb
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // get OP
        instruction::CPY, 1, 3, 0, 102, 100, 0,     // arg0 : OP
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // transcribe the OP : 
        // 0 : +=
        // 1 : -=
        // 2 : *=
        // else : /= 
        instruction::JRE, 0, 1, 0, 5, 102, 0,
        instruction::JRE, 0, 1, 0, 6, 102, 1,
        instruction::JRE, 0, 1, 0, 7, 102, 2,
        instruction::CPY, 1, 0, 0, 102, instruction::DIV, 0,
        instruction::JRA, 0, 0, 0, 6, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::ADD, 0,
        instruction::JRA, 0, 0, 0, 4, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::SUB, 0,
        instruction::JRA, 0, 0, 0, 2, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::MUL, 0,

        // put codons on stack

        // OP 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 1, 0, 101, 102, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg1 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg1 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg2 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // increment/decrement cst address
    std::vector<int> tRNA_INCcst {
        3, id_tRNA_INCcst,
        
        // 2 args : INC/DEC flag, addr cst
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // get OP
        instruction::CPY, 1, 3, 0, 102, 100, 0,     // arg0 : OP
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // transcribe the OP : 
        // 0 : INC
        // else : DEC
        instruction::JRE, 0, 1, 0, 3, 102, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::DEC, 0,
        instruction::JRA, 0, 0, 0, 2, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::INC, 0,

        // put codons on stack

        // OP 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 1, 0, 101, 102, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // cst
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,     // arg1 : cst
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // increment/decrement local var
    std::vector<int> tRNA_INCLV {
        3, id_tRNA_INCLV,
        
        // 2 args : INC/DEC flag, var nb
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // get OP
        instruction::CPY, 1, 3, 0, 102, 100, 0,     // arg0 : OP
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // transcribe the OP : 
        // 0 : INC
        // else : DEC
        instruction::JRE, 0, 1, 0, 3, 102, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::DEC, 0,
        instruction::JRA, 0, 0, 0, 2, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::INC, 0,

        // put codons on stack

        // OP 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 1, 0, 101, 102, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg1 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // increment/decrement dereferenced local var
    std::vector<int> tRNA_INCDLV {
        3, id_tRNA_INCDLV,
        
        // 2 args : INC/DEC flag, var nb
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // get OP
        instruction::CPY, 1, 3, 0, 102, 100, 0,     // arg0 : OP
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // transcribe the OP : 
        // 0 : INC
        // else : DEC
        instruction::JRE, 0, 1, 0, 3, 102, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::DEC, 0,
        instruction::JRA, 0, 0, 0, 2, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::INC, 0,

        // put codons on stack

        // OP 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 1, 0, 101, 102, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg1 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };
    
    // increment/decrement val at top of stack
    std::vector<int> tRNA_INCS {
        3, id_tRNA_INCS,
        
        // 1 arg : INC/DEC flag
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // get OP
        instruction::CPY, 1, 3, 0, 102, 100, 0,     // arg0 : OP
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // transcribe the OP : 
        // 0 : INC
        // else : DEC
        instruction::JRE, 0, 1, 0, 3, 102, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::DEC, 0,
        instruction::JRA, 0, 0, 0, 2, 0, 0,
        instruction::CPY, 1, 0, 0, 102, instruction::INC, 0,

        // put codons on stack

        // OP 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 1, 0, 101, 102, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // stack
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 99, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // call function : cst
    std::vector<int> tRNA_CALLcst {
        3, id_tRNA_CALLcst,

        // 1 arg : func ID
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // CALL
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CALL, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // func ID
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // call function : var
    std::vector<int> tRNA_CALLLV {
        3, id_tRNA_CALLLV,

        // 1 arg : var nb corresponding to func ID
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // CALL
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CALL, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // genetic set : cst <- cst
    std::vector<int> tRNA_GScstcst {
        3, id_tRNA_GScstcst,

        // 2 args : gene pos (cst), val (cst)
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // GSET
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::GSET, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // cst gene pos
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // val
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // genetic set : cst <- var
    std::vector<int> tRNA_GScstLV {
        3, id_tRNA_GScstLV,

        // 2 args : gene pos (cst), val (var nb)
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // GSET
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::GSET, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // cst gene pos
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // genetic set : var <- cst
    std::vector<int> tRNA_GSLVcst {
        3, id_tRNA_GSLVcst,

        // 2 args : gene pos (var), val (cst)
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // GSET
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::GSET, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var gene pos
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // val
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // genetic set : var <- var
    std::vector<int> tRNA_GSLVLV {
        3, id_tRNA_GSLVLV,

        // 2 args : gene pos (var nb), val (var nb)
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // GSET
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::GSET, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var gene pos
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // local var val
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 102, 98, 100,
        instruction::CPY, 3, 2, 0, 101, 102, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // get universe size in var
    std::vector<int> tRNA_USLV {
        3, id_tRNA_USLV,
        
        // 1 arg : var nb
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // CPYUS
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPYUS, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg0 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // read universe cell at local var
    std::vector<int> tRNA_RULV {
        3, id_tRNA_RULV,
        
        // 1 args : var nb
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // READ
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::READ, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg0 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };



    // HALT
    std::vector<int> tRNA_HALT {
        3, id_tRNA_HALT,
        
        // 0 arg
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // HALT 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::HALT, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };


    // custom instructions

    // GPTR special instr
    std::vector<int> tRNA_SP_GPTR {
        3, id_tRNA_SP_GPTR,
        
        // 0 arg
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // GPTR 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::GPTR, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // add to fct ptr special instr
    std::vector<int> tRNA_SP_FCTADD {
        3, id_tRNA_SP_FCTADD,
        
        // 0 arg
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // ADD 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::ADD, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // get fct ptr in var
    std::vector<int> tRNA_SP_GFPTRLV {
        3, id_tRNA_SP_GFPTRLV,
        
        // 1 arg : var to get fct ptr
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // CPY 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg0 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // get stack pos
    std::vector<int> tRNA_SP_GSPLV {
        3, id_tRNA_SP_GSPLV,
        
        // 1 arg : var nb
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        //instruction::CPY, 1, 1, 0, 100, 99, 0,

        // CPY 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg0 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 99
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 99, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // genetic copy between dereferenced vars
    std::vector<int> tRNA_SP_GCPY {
        3, id_tRNA_SP_GCPY,
        
        // 3 arg : var nb, var nb, var nb
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        //instruction::CPY, 1, 1, 0, 100, 99, 0,

        // GCPY 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::GCPY, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg0 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg1 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // local var
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::ADD, 1, 1, 3, 103, 98, 100,    // arg2 : var nb
        instruction::CPY, 3, 2, 0, 101, 103, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };




    // meta tRNA for P-site
    std::vector<int> tRNA_MP {
        3, id_tRNA_MP,
        
        // 0 args
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // CPY 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 100
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 100, 0,
        // 99
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 99, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        // INC 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::INC, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 100
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 100, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // meta tRNA for E-site
    std::vector<int> tRNA_ME {
        3, id_tRNA_ME,
        
        // 0 args
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // DEC 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::DEC, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 99
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 99, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        // CPY 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 99
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 99, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        // INC 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::INC, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 99
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 99, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        // INC 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::INC, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // meta tRNA to copy cst
    std::vector<int> tRNA_Mcst {
        3, id_tRNA_Mcst,
        
        // 1 arg
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // INC 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::INC, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        // CPY 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // val
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // meta tRNA to copy 0
    std::vector<int> tRNA_M0 {
        3, id_tRNA_M0,
        
        // 0 args
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // INC 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::INC, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        // CPY 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // meta tRNA to copy 1
    std::vector<int> tRNA_M1 {
        3, id_tRNA_M1,
        
        // 0 args
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // INC 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::INC, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        // CPY 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };


    // meta tRNA to copy 2
    std::vector<int> tRNA_M2 {
        3, id_tRNA_M2,
        
        // 0 args
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // INC 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::INC, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        // CPY 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // meta tRNA to copy 3
    std::vector<int> tRNA_M3 {
        3, id_tRNA_M3,
        
        // 0 args
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // INC 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::INC, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        // CPY 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // meta tRNA for custom instruction
    std::vector<int> tRNA_MInstr {
        3, id_tRNA_MInstr,
        
        // 1 arg : instr nb
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // INC 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::INC, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        // CPY 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // instr
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,     // arg0 : instr
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // meta tRNA for CPY instr
    std::vector<int> tRNA_MCPY {
        3, id_tRNA_MCPY,
        
        // 0 args
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // INC 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::INC, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        // CPY 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // CPY
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };


    // meta tRNA for arg val
    std::vector<int> tRNA_Marg {
        3, id_tRNA_Marg,
        
        // 0 args
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // INC 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::INC, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        // CPY 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 100
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 100, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        // INC 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::INC, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 100
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 100, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        instruction::JMP, 2, 0, 0, 0, 0, 0
    };


    // meta tRNA for arg val without increment of the metavar stack
    std::vector<int> tRNA_MargW {
        3, id_tRNA_MargW,
        
        // 0 args
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // INC 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::INC, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        // CPY 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 100
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 100, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // meta tRNA to LV
    std::vector<int> tRNA_MLV {
        3, id_tRNA_MLV,
        
        // 0 args
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // INC 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::INC, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        // ADD 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::ADD, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 1
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 1, 0,
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
        // 103
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 103, 0,
        // 98
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 98, 0,
        // 100
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 100, 0,


        // CPY 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 103
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 103, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        // INC 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::INC, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 100
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 100, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // meta tRNA to LV without increment of the metavar stack
    std::vector<int> tRNA_MLVW {
        3, id_tRNA_MLVW,
        
        // 0 args
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack

        // INC 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::INC, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,


        // CPY 
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::CPY, 0,
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 101
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 101, 0,
        // 103
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 103, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };


    // return (JMP02)
    std::vector<int> tRNA_RET {
        3, id_tRNA_RET,
        
        // 0 arg 
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // get E site
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,   // E site in 101

        // put codons on stack
        // JMP
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, instruction::JMP, 0,
        // 2
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 2, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };



    std::map<std::string, std::vector<int>> all_parts {
        { "tRNA : create vars", tRNA_CVARS },
        { "tRNA : init vars", tRNA_IVARS },
        { "tRNA : set local var to cst", tRNA_SLVcst },
        { "tRNA : set dereferenced local var by cst", tRNA_SDLVcst },
        { "tRNA : set local var to local var", tRNA_SLVLV },
        { "tRNA : set dereferenced local var by local var", tRNA_SDLVLV },
        { "tRNA : set local var to dereferenced local var", tRNA_SLVDLV },
        { "tRNA : set dereferenced local var by dereferenced local var", tRNA_SDLVDLV },
        { "tRNA : set const addr with LV", tRNA_ScstLV},
        { "tRNA : set LV with cst addr", tRNA_SLVaddr},
        { "tRNA : read gene at local var in local var", tRNA_RGLVLV },
        { "tRNA : write genes at dereferenced vars", tRNA_WGDLV},
        { "tRNA : get input in local var", tRNA_GILV },
        { "tRNA : get dereferenced input in local var", tRNA_GDILV },
        { "tRNA : get input in dereferenced local var", tRNA_GIDLV },
        { "tRNA : get dereferenced input in dereferenced local var", tRNA_GDIDLV },
        { "tRNA : get top of stack in local var", tRNA_GTSLV },
        { "tRNA : get top of stack in local var with decrement", tRNA_GTSLVD },
        { "tRNA : get top of stack in dereferenced local var", tRNA_GTSDLV },
        { "tRNA : get local var in output", tRNA_GLVO },
        { "tRNA : jump IF 0", tRNA_IF0 },
        { "tRNA : size of if jump", tRNA_SIJ },
        { "tRNA : size of else jump", tRNA_SEJ },
        { "tRNA : size of while jump", tRNA_SWJ },
        { "tRNA : jump var", tRNA_JLV },
        { "tRNA : set output size with cst", tRNA_SOScst },
        { "tRNA : set output size with local var", tRNA_SOSLV },
        { "tRNA : get input size", tRNA_GISLV },
        { "tRNA : put cst on stack with increment", tRNA_PCSI },
        { "tRNA : put local var on stack with increment", tRNA_PLVSI },
        { "tRNA : put cst on stack without increment", tRNA_PCSWI },
        { "tRNA : put local var on stack without increment", tRNA_PLVSWI },
        { "tRNA : compare local var with constant", tRNA_CMPLVcst },
        { "tRNA : compare local var with local var", tRNA_CMPLVLV },
        { "tRNA : var op-equal cst addr cst arg", tRNA_OPEcstcst },
        { "tRNA : var op-equal cst addr var arg", tRNA_OPEcstLV },
        { "tRNA : var op-equal var with cst arg", tRNA_OPELVcst },
        { "tRNA : var op-equal var with var arg", tRNA_OPELVLV },
        { "tRNA : increment/decrement cst address", tRNA_INCcst },
        { "tRNA : increment/decrement at local var", tRNA_INCLV },
        { "tRNA : increment/decrement at dereferenced local var", tRNA_INCDLV },
        { "tRNA : increment/decrement stack", tRNA_INCS },
        { "tRNA : call func cst ID", tRNA_CALLcst },
        { "tRNA : call func cst var", tRNA_CALLLV },
        { "tRNA : set gene at cst to cst", tRNA_GScstcst },
        { "tRNA : set gene at cst to var", tRNA_GScstLV },
        { "tRNA : set gene at var to cst", tRNA_GSLVcst },
        { "tRNA : set gene at var to var", tRNA_GSLVLV },
        { "tRNA : get universe size in var", tRNA_USLV },
        { "tRNA : read universe at local var", tRNA_RULV },
        { "tRNA : halt", tRNA_HALT },
        // special tRNAs
        { "tRNA : change prog ptr special tRNA", tRNA_SP_GPTR },
        { "tRNA : add fct ptr specil tRNA", tRNA_SP_FCTADD },
        { "tRNA : get fct ptr in var", tRNA_SP_GFPTRLV },
        { "tRNA : get stack pos in var", tRNA_SP_GSPLV },
        { "tRNA : copy molecular body between vars", tRNA_SP_GCPY },
        // meta tRNAs
        { "tRNA : meta P-site", tRNA_MP },
        { "tRNA : meta E-site", tRNA_ME },
        { "tRNA : meta cpy cst", tRNA_Mcst },
        { "tRNA : meta cpy 0", tRNA_M0 },
        { "tRNA : meta cpy 1", tRNA_M1 },
        { "tRNA : meta cpy 2", tRNA_M2 },
        { "tRNA : meta cpy 3", tRNA_M3 },
        { "tRNA : meta instr", tRNA_MInstr },
        { "tRNA : meta CPY", tRNA_MCPY },
        { "tRNA : meta arg", tRNA_Marg },
        { "tRNA : meta arg without increment", tRNA_MargW },
        { "tRNA : meta LV", tRNA_MLV },
        { "tRNA : meta LV without increment", tRNA_MLVW },
        { "tRNA : return", tRNA_RET }
    };

    return all_parts;
}

void GeneToProgtein::exec_step_2(sp_univ_evo_algos universe, sp_evox algo)
{
    // get functions
    auto molecular_body_parts = this->get_tRNAs_1();

    std::vector<std::string> iteration_order {
        "tRNA : create vars",
        "tRNA : init vars",
        "tRNA : set local var to cst",
        "tRNA : set dereferenced local var by cst",
        "tRNA : set local var to local var",
        "tRNA : set dereferenced local var by local var",
        "tRNA : set local var to dereferenced local var",
        "tRNA : set dereferenced local var by dereferenced local var",
        "tRNA : set const addr with LV",
        "tRNA : set LV with cst addr",
        "tRNA : read gene at local var in local var",
        "tRNA : write genes at dereferenced vars",
        "tRNA : get input in local var",
        "tRNA : get dereferenced input in local var",
        "tRNA : get input in dereferenced local var",
        "tRNA : get dereferenced input in dereferenced local var",
        "tRNA : get top of stack in local var",
        "tRNA : get top of stack in local var with decrement",
        "tRNA : get top of stack in dereferenced local var",
        "tRNA : get local var in output",
        "tRNA : jump IF 0",
        "tRNA : size of if jump",
        "tRNA : size of else jump",
        "tRNA : size of while jump",
        "tRNA : jump var",
        "tRNA : set output size with cst",
        "tRNA : set output size with local var",
        "tRNA : get input size",
        "tRNA : put cst on stack with increment",
        "tRNA : put local var on stack with increment",
        "tRNA : put cst on stack without increment",
        "tRNA : put local var on stack without increment",
        "tRNA : compare local var with constant",
        "tRNA : var op-equal cst addr cst arg",
        "tRNA : var op-equal cst addr var arg",
        "tRNA : var op-equal var with cst arg",
        "tRNA : var op-equal var with var arg",
        "tRNA : increment/decrement cst address",
        "tRNA : increment/decrement at local var",
        "tRNA : increment/decrement at dereferenced local var",
        "tRNA : increment/decrement stack",
        "tRNA : compare local var with local var",
        "tRNA : call func cst ID",
        "tRNA : call func cst var",
        "tRNA : set gene at cst to cst",
        "tRNA : set gene at cst to var",
        "tRNA : set gene at var to cst",
        "tRNA : set gene at var to var",
        "tRNA : get universe size in var",
        "tRNA : read universe at local var",
        "tRNA : halt",
        // special tRNAs
        "tRNA : change prog ptr special tRNA",
        "tRNA : add fct ptr specil tRNA",
        "tRNA : get fct ptr in var",
        "tRNA : get stack pos in var",
        "tRNA : copy molecular body between vars", 
        // meta tRNAs
        "tRNA : meta P-site",
        "tRNA : meta E-site",
        "tRNA : meta cpy cst",
        "tRNA : meta cpy 0",
        "tRNA : meta cpy 1",
        "tRNA : meta cpy 2",
        "tRNA : meta cpy 3",
        "tRNA : meta instr",
        "tRNA : meta CPY",
        "tRNA : meta arg",
        "tRNA : meta arg without increment",
        "tRNA : meta LV",
        "tRNA : meta LV without increment",
        "tRNA : return"
    };

    for(int i=0;i<iteration_order.size();i++)
    {
        std::string step_name = iteration_order[i];
        std::vector<int> molecular_body_part = molecular_body_parts[step_name];

        sp_free_molecules free_molecules = std::make_shared<FreeMolecules>("free molecules");
        free_molecules->init();
        free_molecules->set_molecular_body(molecular_body_part);

        // tell the algo to get the code
        std::vector<int> input{ 3, molecular_body_part[1] };
        algo->set_input(input);

        universe->get_places()[2]->set_entity(free_molecules);

        universe->exec();
    }

    universe->exec();

    write_molecular_body_to_csv(algo->get_molecular_body(), "molecular_body_with_tRNAs.csv");
}

//-------------------- step 3

std::vector<int> GeneToProgtein::get_ribosome()
{
    // input : mRNA initialised, i.e. :
    // - mRNA end is set
    // - RNA sequence starts at stack+2
    std::vector<int> ribosome {
        3, 206,

        instruction::ADD, 1, 1, 0, 99, 99, 2,

        // create progtein ptr
        instruction::CPY, 1, 2, 0, 100, 99, 0,
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::CPY, 2, 1, 0, 100, 100, 0,

        // init ribosome ptr
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::CPY, 2, 1, 0, 100, 100, 0,
        instruction::ADD, 2, 2, 0, 100, 100, 2,

        // call tRNAs until the end of mRNA
        // get ribosome ptr (P site)
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::INC, 1, 0, 0, 100, 0, 0,
        // stop if ribosome ptr > mRNA end
        instruction::JRG, 0, 2, 2, 5, 100, 99,
        // call tRNA
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CALL, 0, 3, 0, 0, 100, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::JRS, 0, 0, 0, 6, 0, 0,

        // remove the mRNA
        // compute nb of amino-acids
        instruction::CPY, 1, 2, 0, 100, 99, 0,
        instruction::INC, 1, 0, 0, 100, 0, 0,   // progtein ptr pos
        instruction::CPY, 1, 2, 0, 101, 100, 0, // progtein ptr val
        instruction::SUB, 1, 2, 1, 102, 100, 100,   // nb of amino-acids
        instruction::ADD, 2, 1, 1, 99, 99, 102,
        instruction::CPY, 1, 1, 0, 103, 99, 0,  // cpy dest
        instruction::ADD, 1, 1, 0, 103, 103, 7,
        // copy progtein at top of stack
        instruction::JRGE, 0, 1, 1, 5, 100, 101,
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::INC, 1, 0, 0, 103, 0, 0,
        instruction::CPY, 2, 2, 0, 103, 100, 0,
        instruction::JRS, 0, 0, 0, 4, 0, 0,
        
        instruction::ADD, 2, 2, 0, 99, 99, 7,
        instruction::SUB, 1, 1, 0, 99, 99, 2,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    return ribosome;
}

void GeneToProgtein::exec_step_3(sp_univ_evo_algos universe, sp_evox algo)
{
    //----- get ribosome

    std::vector<int> ribosome = get_ribosome();

    sp_free_molecules free_molecules = std::make_shared<FreeMolecules>("free molecules");
    free_molecules->init();
    free_molecules->set_molecular_body(ribosome);
    universe->get_places()[1]->set_entity(free_molecules);

    algo->set_input({3, 206});
    universe->exec();

    // call ribosome for Heaviside ad hoc mRNA

    int stack_pos = 153;
    int size_arn = 32;

    algo->set_data_at(stack_pos, stack_pos+size_arn);
    algo->set_data_at(stack_pos+1,0);
    algo->set_data_at(stack_pos+2,0);
    algo->set_data_at(stack_pos+3,10000);
    algo->set_data_at(stack_pos+4,1000);
    algo->set_data_at(stack_pos+5,3);
    algo->set_data_at(stack_pos+6,10001);
    algo->set_data_at(stack_pos+7,10200);
    algo->set_data_at(stack_pos+8,1);
    algo->set_data_at(stack_pos+9,2);
    algo->set_data_at(stack_pos+10,11300);
    algo->set_data_at(stack_pos+11,2);
    algo->set_data_at(stack_pos+12,1);
    algo->set_data_at(stack_pos+13,heaviside_threshold);
    algo->set_data_at(stack_pos+14,2);
    algo->set_data_at(stack_pos+15,10500);
    algo->set_data_at(stack_pos+16,2);
    algo->set_data_at(stack_pos+17,10100);
    algo->set_data_at(stack_pos+18,3);
    algo->set_data_at(stack_pos+19,1);
    algo->set_data_at(stack_pos+20,10600);
    algo->set_data_at(stack_pos+21,10100);
    algo->set_data_at(stack_pos+22,3);
    algo->set_data_at(stack_pos+23,0);
    algo->set_data_at(stack_pos+24,10700);
    algo->set_data_at(stack_pos+25,11000);
    algo->set_data_at(stack_pos+26,1);
    algo->set_data_at(stack_pos+27,10250);
    algo->set_data_at(stack_pos+28,0);
    algo->set_data_at(stack_pos+29,3);
    algo->set_data_at(stack_pos+30,11150);
    algo->set_data_at(stack_pos+31,3);
    algo->set_data_at(stack_pos+32,9999);
    
    algo->set_input({-1, 206});
    universe->exec();

    // get built protein ad hoc from data

    std::vector<int> built_progtein(100);
    built_progtein[0] = 3;
    built_progtein[1] = 667;
    for(int i=0;i<98;i++)
        built_progtein[2+i] = algo->get_data()[stack_pos+8+i];


    // add heaviside progtein to funcs

    sp_free_molecules free_molecules_heaviside_built = std::make_shared<FreeMolecules>("Heaviside built progtein");
    free_molecules_heaviside_built->init();

    free_molecules_heaviside_built->set_molecular_body(built_progtein);
    universe->get_places()[1]->set_entity(free_molecules_heaviside_built);

    algo->set_input({3, 667});
    universe->exec();

    //----- test Heaviside function

    int nb_test_inputs = 20;
    bool passed = true;
    for(int i=0;i<nb_test_inputs;i++)
    {
        int test_input = rand_gen::rand_normal(heaviside_threshold, 4);
        int expected_output = test_input > heaviside_threshold ? 1 : 0;

        algo->set_input({-1, 667, test_input});
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

    write_molecular_body_to_csv(algo->get_molecular_body(), "molecular_body_with_ribosome_and_built_heaviside.csv");
}

//-------------------- step 4

std::map<std::string, std::vector<int>> GeneToProgtein::get_DNA_and_RNAP()
{
    // DNA
    std::vector<int> DNA_Heaviside {
        3, -1,
        0, 0, 0, 0, 0, GSTART_ID, 667,
        10000, 1000, 3, 10001, 10200, 1, 2,
        11300, 2, 1,  heaviside_threshold, 2, 10500, 2,
        10100, 3, 1, 10600, 10100, 3, 0,
        10700, 11000, 1, 10250, 0, 3, 11150,
        3, 9999, GSTOP_ID, 0, 0, 0, 0,
    };

    // RNAP
    std::vector<int> RNAP {
        3, 207,

        // first, find teleonomical ID after start ID
        instruction::CPY, 1, 0, 0, 110, -7, 0,
        instruction::ADD, 1, 1, 0, 110, 110, 7,
        instruction::GR, 1, 2, 0, 101, 110, 0,
        instruction::JRE, 0, 1, 0, 2, 101, instruction::MARKER, // marker found
        instruction::JRS, 0, 0, 0, 3, 0, 0,
        // check func id
        instruction::ADD, 1, 1, 0, 110, 110, 2,
        instruction::GR, 1, 2, 0, 101, 110, 0,
        instruction::JRE, 0, 1, 0, 3, 101, -1,
        instruction::SUB, 1, 1, 0, 110, 110, 2,
        instruction::JRS, 0, 0, 0, 8, 0, 0,
        
        // finds start markers and corresponding teleonomical ID
        instruction::CPY, 1, 2, 0, 100, 99, 0,      // get arg from stack
        instruction::INC, 1, 0, 0, 110, 0, 0,
        instruction::GR, 1, 2, 0, 101, 110, 0,
        instruction::JRE, 0, 1, 0, 2, 101, GSTART_ID, // marker found
        instruction::JRS, 0, 0, 0, 3, 0, 0,
        // check func id
        instruction::INC, 1, 0, 0, 110, 0, 0,
        instruction::GR, 1, 2, 0, 101, 110, 0,
        instruction::JRE, 0, 1, 1, 3, 101, 100,
        instruction::DEC, 1, 0, 0, 110, 0, 0,
        instruction::JRS, 0, 0, 0, 8, 0, 0,

        // then, write on stack untill stop ID
        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 1, 0, 101, 99, 0,      // loop ptr
        // pass ribosome ptr and place for ID
        instruction::INC, 1, 0, 0, 101, 0, 0,
        instruction::CPY, 2, 0, 0, 101, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,
        instruction::CPY, 2, 0, 0, 101, 0, 0,
        // loop over codons
        instruction::INC, 1, 0, 0, 110, 0, 0,
        instruction::INC, 1, 0, 0, 101, 0, 0,
        instruction::GR, 2, 2, 0, 101, 110, 0,
        instruction::JRE, 0, 2, 0, 2, 101, GSTOP_ID, // marker found
        instruction::JRS, 0, 0, 0, 4, 0, 0,
        // stop marker found
        instruction::DEC, 1, 0, 0, 101, 0, 0,
        instruction::CPY, 2, 1, 0, 99, 101, 0,
        instruction::SUB, 1, 1, 0, 99, 99, 2,
        instruction::CPY, 2, 1, 0, 99, 100, 0,


        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // transcriber
    // handles the whole transcription process : RNAP, ribosome, write to code
    std::vector<int> transcriber {
        3, 208,

        instruction::INC, 1, 0, 0, 99, 0, 0,
        instruction::CPYIN, 2, 1, 0, 99, 2, 0,
        // transcribe DNA to RNA
        instruction::CALL, 0, 0, 0, 0, 207, 0,
        // transcribe RNA to progtein
        instruction::CALL, 0, 0, 0, 0, 206, 0,

        // add the markers

        // begin
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::ADD, 1, 1, 0, 100, 100, 3,
        instruction::CPY, 1, 1, 0, 101, 100, 0,
       
        // MARKER
        instruction::CPY, 2, 0, 0, 100, instruction::MARKER, 0,
        // 0
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::CPY, 2, 0, 0, 100, 0, 0,
        // func ID
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::CPY, 2, 2, 0, 100, 99, 0,
        // 0
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::CPY, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::CPY, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::CPY, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::CPY, 2, 0, 0, 100, 0, 0,

        // end
        instruction::CPY, 1, 1, 0, 100, 99, 0,
        instruction::ADD, 1, 1, 0, 100, 100, 2,
        instruction::CPY, 1, 2, 0, 100, 100, 0,
        instruction::INC, 1, 0, 0, 100, 0, 0,
        
        // MARKER
        instruction::CPY, 2, 0, 0, 100, instruction::MARKER, 0,
        // 0
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::CPY, 2, 0, 0, 100, 0, 0,
        // func ID
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::CPY, 2, 2, 0, 100, 99, 0,
        // 0
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::CPY, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::CPY, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::CPY, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::CPY, 2, 0, 0, 100, 0, 0,

        // copy into molecular body
        // find end of molecular body
        instruction::CPY, 1, 0, 0, 103, -7, 0,
        instruction::ADD, 1, 1, 0, 103, 103, 7,
        instruction::GR, 1, 2, 0, 102, 103, 0,
        instruction::JRE, 0, 0, 1, 2, instruction::MARKER, 102, // check if we are on a marker
        instruction::JRS, 0, 0, 0, 3, 0, 0,
        instruction::INC, 1, 0, 0, 103, 0, 0,
        instruction::GR, 1, 2, 0, 102, 103, 0,
        instruction::DEC, 1, 0, 0, 103, 0, 0,
        instruction::JRE, 0, 0, 1, 2, -1, 102,  // check that marker ID is -1
        instruction::JRS, 0, 0, 0, 8, 0, 0,
 
        instruction::GCPY, 2, 2, 2, 103, 101, 100,


        instruction::JMP, 2, 0, 0, 0, 0, 0
    };


    std::map<std::string, std::vector<int>> all_parts {
        { "Heaviside DNA", DNA_Heaviside },
        { "RNAP", RNAP },
        { "transcriber", transcriber}
    };

    return all_parts;
}

void GeneToProgtein::exec_step_4(sp_univ_evo_algos universe, sp_evox algo)
{
    // get functions
    auto molecular_body_parts = this->get_DNA_and_RNAP();

    std::vector<std::string> iteration_order {
        "Heaviside DNA",
        "RNAP",
        "transcriber"
    };

    for(int i=0;i<iteration_order.size();i++)
    {
        std::string step_name = iteration_order[i];
        std::vector<int> molecular_body_part = molecular_body_parts[step_name];

        sp_free_molecules free_molecules = std::make_shared<FreeMolecules>("free molecules");
        free_molecules->init();
        free_molecules->set_molecular_body(molecular_body_part);

        // tell the algo to get the code
        std::vector<int> input{ 3, molecular_body_part[1] };
        algo->set_input(input);

        universe->get_places()[2]->set_entity(free_molecules);

        universe->exec();
    }

    algo->set_max_nb_instr_exec(10000*12);
    algo->set_input({-1, 208, 667 });
    universe->exec();

 
    write_molecular_body_to_csv(algo->get_molecular_body(), "molecular_body_base_self_transcription.csv");
}