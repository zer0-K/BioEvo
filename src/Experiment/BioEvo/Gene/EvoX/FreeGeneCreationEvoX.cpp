#include "FreeGeneCreationEvoX.hpp"

#include <fstream>

#include "../../../../Utils/Functions.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/UtilityFunctions.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/InstructionMapping.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/FreeGenes.hpp"

/*
Teleonomical IDs of high orders:
    - order 0 : 1,000,000
    - order 1 : 1,001,000
    - order 2 : 2,000,000
    - ...
    - order n : n*1,000,000


order 0 generation:
    - 1,000,000 : instruction ID
    - 1,000,001 : arg orders (0,1,2)
    - 1,000,002 : stack & local var pos (99,100,...)
    - 1,000,003 : arg values
    - ...

order 1 generation:
    - increment/decrement
    - math operations
    - atomic stack management
    - function call
    - ...

order 2 generation:
    - basic math expressions
    - if/else
    - loops
    - basic stack management
    - ...

*/

FreeGeneCreationEvoX::FreeGeneCreationEvoX()
    :Experiment::Experiment(name_exp_bioevo_genes_evox_fgc)
{
    init();
}

void FreeGeneCreationEvoX::init()
{

}

void FreeGeneCreationEvoX::launch()
{
    // initialisation : create algo, universe, and add the algo the funcs needed for the experiment
    sp_evox algo = get_base_algo("algo");
    sp_univ_evo_algos universe = get_universe(algo);
    provide_experiment_functions(universe, algo);

    // run the experiment after initialisation
    exec(universe, algo);
}

sp_univ_evo_algos FreeGeneCreationEvoX::get_universe(sp_evox algo) 
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

sp_evox FreeGeneCreationEvoX::get_base_algo(std::string name)
{
    // create algo
    sp_evox algo = std::make_shared<EvoX>(name);
    algo->init();

    // get genes from csv
    std::vector<int> genes = get_genes_from_csv("genes_base.csv");
    algo->set_genes(genes);

    // set data stack at 150
    algo->set_data_at(99, 150);

    return algo;
}

std::map<std::string, std::vector<int>> FreeGeneCreationEvoX::get_utility_generators()
{
    // copy input args to stack in reverse order
    std::vector<int> copy_in_to_stack {
        3, 203,

        instruction::CPYIS, 1, 0, 0, 100, 0, 0,
        // beginning of loop
        instruction::DEC, 1, 0, 0, 100, 0, 0,
        instruction::INC, 1, 0, 0, 99, 0, 0,    // will copy input on stack
        instruction::CPYIN, 2, 2, 0, 99, 100, 0,    // reverse order
        instruction::JRE, 0, 1, 0, 2, 100, 2,    // ignore first 2 args
        instruction::JRS, 0, 0, 0, 4, 0, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };

    // given input, generate free genes
    std::vector<int> generate_free_genes {
        3, 204,

        instruction::CALL, 0, 0, 0, 0, 203, 0,
        // remove generator ID from stack
        instruction::CPY, 1, 2, 0, 100, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        // call the generator
        instruction::CALL, 0, 1, 0, 0, 100, 0,
        // copy the generator out to out
        instruction::SETOS, 0, 0, 0, 1, 0, 0,
        instruction::CPYOUT, 1, 2, 0, 0, 99, 0,

        instruction::JMP, 2, 0, 0, 0, 0, 0
    };


    std::map<std::string, std::vector<int>> all_parts {
        { "copy input to stack", copy_in_to_stack },
        { "generate free genes", generate_free_genes }
    };

    return all_parts;
}

std::map<std::string, std::vector<int>> FreeGeneCreationEvoX::get_generators_order_0()
{
    // when provided a number, interprete it as the id of an instruction
    std::vector<int> generator_order_0_instruction {
        3, 1000000,

        // compute arg modulo nb of instructions
        instruction::DIV, 1, 2, 0, 100, 99, instruction::size,
        instruction::JRE, 0, 1, 0, 3, 100, 0,
        // if |arg|>= size ( => scale in ]-size;size[ )
        instruction::MUL, 1, 1, 0, 100, 100, instruction::size,
        instruction::SUB, 2, 2, 1, 99, 99, 100,
        // if -size < arg < size
        instruction::JRL, 0, 2, 0, 2, 99, 0,    // if  -size < arg < 0
        instruction::JMP, 2, 0, 0, 0, 0, 0,
        instruction::ADD, 2, 2, 0, 99, 99, instruction::size, 

        instruction::JMP, 2, 0, 0, 0, 0, 0,
    };

    // generate the deepness of args with a random geometric distrib
    std::vector<int> generator_order_0_arg_deepness {
        3, 1000001,

        // parameters : a, b, for geom distrib with param p=a/b
        instruction::CPY, 1, 2, 0, 100, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::RG, 2, 1, 1, 99, 100, 101,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
    };

    // generate the args values with a random geometric distrib
    std::vector<int> generator_order_0_arg_vals {
        3, 1000002,

        // parameters : a, b, for geom distrib with param p=a/b
        // final nb = 99 + random geometric
        instruction::CPY, 1, 2, 0, 100, 99, 0,
        instruction::DEC, 1, 0, 0, 99, 0, 0,
        instruction::CPY, 1, 2, 0, 101, 99, 0,
        instruction::RG, 2, 1, 1, 99, 100, 101,
        instruction::ADD, 2, 2, 0, 99, 99, 99,

        instruction::JMP, 2, 0, 0, 0, 0, 0,
    };


    std::map<std::string, std::vector<int>> all_parts {
        { "order 0 : instruction", generator_order_0_instruction },
        { "order 0 : arg deepness", generator_order_0_arg_deepness },
        { "order 0 : arg values", generator_order_0_arg_vals }
    };

    return all_parts;
}

std::map<std::string, std::vector<int>> FreeGeneCreationEvoX::get_generators_order_1()
{
    std::map<std::string, std::vector<int>> all_parts {

    };

    return all_parts;
}

std::map<std::string, std::vector<int>> FreeGeneCreationEvoX::get_generators_order_2()
{
    std::map<std::string, std::vector<int>> all_parts {

    };

    return all_parts;
}

std::map<std::string, std::vector<int>> FreeGeneCreationEvoX::merge_generators(std::vector<std::map<std::string, std::vector<int>>> generators)
{
    std::map<std::string, std::vector<int>> all_parts {};

    for(int i=0;i<generators.size();i++)
    {
        for(auto const& [generator_name, generator_code] : generators[i])
        {
            all_parts[generator_name] = generator_code;
        }
    }

    return all_parts;
}


void FreeGeneCreationEvoX::provide_experiment_functions(sp_univ_evo_algos universe, sp_evox algo)
{
    //----- first, add order 0 generators
    std::vector<std::map<std::string, std::vector<int>>> generators_list_by_order {
        get_utility_generators(),
        get_generators_order_0(),
        get_generators_order_1(),
        get_generators_order_2()
    };

    auto all_generators = merge_generators(generators_list_by_order);

    for(auto const& [generator_name, generator_code] : all_generators)
    {
        // create freegenes with the generator's code
        sp_freegenes freegenes = std::make_shared<FreeGenes>("free genes " + generator_name);
        freegenes->init();
        freegenes->set_genes(generator_code);

        universe->get_places()[2]->set_entity(freegenes);

        // tell the algo to get the code
        std::vector<int> input{ 3, generator_code[1] };
        algo->set_input(input);

        // execute
        universe->exec();
    }

    universe->exec();

    //write_genes_to_csv(algo->get_genes(), "debug.csv");
}

void FreeGeneCreationEvoX::exec(sp_univ_evo_algos universe, sp_evox algo)
{
    std::vector<int> input_test { 5, 204, 1000002, 9, 10 };

    const int nb_loops = 1000;
    const int nb_val = 10;
    std::array<int, nb_val> res_distrib;
    for(int i=0;i<nb_val;i++)
        res_distrib[i] = 0;


    for(int i=0; i<nb_loops;i++)
    {
        algo->set_input(input_test);
        universe->exec();

        auto res = algo->get_output();

        if(res.size()==1)
        {
            if(res[0]-99>nb_val-1)
            {
                res_distrib[nb_val-1] +=1;
            }
            else
            {
                res_distrib[res[0]-99] += 1;
            }
        }
    }

    double test = 1;

}