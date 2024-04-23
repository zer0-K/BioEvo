#include "GeneToProgtein.hpp"

#include <fstream>

#include "../../../../Utils/Functions.hpp"
#include "../../../../Utils/Maths/RandomGen.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/FreeGenes.hpp"


/**
 * Teleonomical IDs of interpretation proteins :
 *  - 10000 : INIT, init
 *  - 10100 : NLV, new local var
 *  - 10200 : GILV, get input in local var
 * 
*/


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
    exec_step_2(univ, algo);
    exec_step_3(univ, algo);
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

//-------------------- step 2

std::map<std::string, std::vector<int>> GeneToProgtein::get_tRNAs_1() 
{
    // note :
    // ribosome increments stack before calling so that
    // we can add fct ID on stack for meta exec
    // --> stack should be pointing to ribosome ptr initially

    // create n vars
    std::vector<int> tRNA_CVARS {
        3, 10000,

        // 2 args : position of heap and nb of vars
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
        3, 10001,

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
        3, 10100,
        
        // 2 args : arg nb, arg val (const) 
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
        // input index
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 3, 0, 101, 100, 0,
        instruction::INC, 2, 0, 0, 100, 0, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // get input into local variable
    std::vector<int> tRNA_GILV {
        3, 10200,

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

    // get local var into output
    std::vector<int> tRNA_GLVO {
        3, 10250,

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
        3, 10500,
        
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
        3, 10600,
        
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
        3, 10700,
        
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

    // set output size (cst)
    std::vector<int> tRNA_SOScst {
        3, 11000,
        
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

    // put const on stack with increment
    std::vector<int> tRNA_PCSI {
        3, 11100,
        
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
        3, 11150,
        
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
        3, 11200,
        
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
        // 1 - increment size of stack
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
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
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
        3, 11250,
        
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
        // 1 - increment size of stack
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
        // 3
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 3, 0,
        // 0
        instruction::INC, 2, 0, 0, 101, 0, 0,
        instruction::CPY, 3, 0, 0, 101, 0, 0,
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
        3, 11300,
        
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
        instruction::JRE, 0, 1, 0, 4, 102, 0,
        instruction::JRE, 0, 1, 0, 6, 102, 1,
        instruction::JRE, 0, 1, 0, 8, 102, 2,
        instruction::JRE, 0, 1, 0, 10, 102, 3,
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
        3, 11350,
        
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
        instruction::JRE, 0, 1, 0, 4, 102, 0,
        instruction::JRE, 0, 1, 0, 6, 102, 1,
        instruction::JRE, 0, 1, 0, 8, 102, 2,
        instruction::JRE, 0, 1, 0, 10, 102, 3,
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

    // return (JMP02)
    std::vector<int> tRNA_RET {
        3, 9999,
        
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
        { "tRNA : get input in local var", tRNA_GILV },
        { "tRNA : get local var in output", tRNA_GLVO },
        { "tRNA : jump IF 0", tRNA_IF0 },
        { "tRNA : size of if jump", tRNA_SIJ },
        { "tRNA : size of else jump", tRNA_SEJ },
        { "tRNA : set output size", tRNA_SOScst },
        { "tRNA : put cst on stack with increment", tRNA_PCSI },
        { "tRNA : put local var on stack with increment", tRNA_PLVSI },
        { "tRNA : put cst on stack without increment", tRNA_PCSWI },
        { "tRNA : put local var on stack without increment", tRNA_PLVSWI },
        { "tRNA : compare local var with constant", tRNA_CMPLVcst },
        { "tRNA : compare local var with local var", tRNA_CMPLVLV },
        { "tRNA : return", tRNA_RET }
    };

    return all_parts;
}

void GeneToProgtein::exec_step_2(sp_univ_evo_algos universe, sp_evox algo)
{
    // get functions for autopoiesis
    auto genome_parts = this->get_tRNAs_1();

    //----- trigger autopoiesis

    std::vector<std::string> iteration_order {
        "tRNA : create vars",
        "tRNA : init vars",
        "tRNA : set local var to cst",
        "tRNA : get input in local var",
        "tRNA : get local var in output",
        "tRNA : jump IF 0",
        "tRNA : size of if jump",
        "tRNA : size of else jump",
        "tRNA : set output size",
        "tRNA : put cst on stack with increment",
        "tRNA : put local var on stack with increment",
        "tRNA : put cst on stack without increment",
        "tRNA : put local var on stack without increment",
        "tRNA : compare local var with constant",
        "tRNA : compare local var with local var",
        "tRNA : return"
    };

    for(int i=0;i<iteration_order.size();i++)
    {
        std::string step_name = iteration_order[i];
        std::vector<int> genome_part = genome_parts[step_name];

        sp_freegenes freegenes = std::make_shared<FreeGenes>("free genes");
        freegenes->init();
        freegenes->set_genes(genome_part);

        // tell the algo to get the code
        std::vector<int> input{ 3, genome_part[1] };
        algo->set_input(input);

        universe->get_places()[2]->set_entity(freegenes);

        universe->exec();
    }

    universe->exec();

    write_genes_to_csv(algo->get_genes(), "genes_with_tRNAs.csv");

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
        // copy progtein at top of stack
        instruction::JRGE, 0, 1, 1, 5, 100, 101,
        instruction::INC, 1, 0, 0, 100, 0, 0,
        instruction::INC, 1, 0, 0, 103, 0, 0,
        instruction::CPY, 2, 2, 0, 103, 100, 0,
        instruction::JRS, 0, 0, 0, 4, 0, 0,
        
        instruction::SUB, 1, 1, 0, 99, 99, 2,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    return ribosome;
}

void GeneToProgtein::exec_step_3(sp_univ_evo_algos universe, sp_evox algo)
{
    int heaviside_threshold = 21;

    //----- get ribosome

    std::vector<int> ribosome = get_ribosome();

    sp_freegenes freegenes = std::make_shared<FreeGenes>("free genes");
    freegenes->init();
    freegenes->set_genes(ribosome);
    universe->get_places()[1]->set_entity(freegenes);

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
        built_progtein[2+i] = algo->get_data()[stack_pos+1+i];


    // add heaviside progtein to funcs

    sp_freegenes freegenes_heaviside_built = std::make_shared<FreeGenes>("Heaviside built progtein");
    freegenes_heaviside_built->init();

    freegenes_heaviside_built->set_genes(built_progtein);
    universe->get_places()[1]->set_entity(freegenes_heaviside_built);

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

    write_genes_to_csv(algo->get_genes(), "genes_with_ribosome_and_built_heaviside.csv");

    std::cout << "Experience over" << std::endl;
}

