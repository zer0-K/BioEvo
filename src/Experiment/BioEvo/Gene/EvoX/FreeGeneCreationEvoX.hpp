#pragma once

#include <map>

#include "../../../Experiment.hpp"

#include "../../../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/EvoX.hpp"

class FreeGeneCreationEvoX : public Experiment
{
protected:
    /**
     * @brief get utility functions for generators
     *
     * The codes are in a freegenes format
     *
     * @return a map of utility functions for the generators
     */
    std::map<std::string, std::vector<int>> get_utility_generators();


    /**
     * @brief get grammars or other generators for order 0 elements (integer)
     *
     * The generators' codes are in a freegenes format
     *
     * @param generators list of the maps of generators (map<generator name,generator code>)
     *
     * @return a merged map of the all generators
     */
    std::map<std::string, std::vector<int>> merge_generators(std::vector<std::map<std::string, std::vector<int>>> generators);


    /**
     * @brief get grammars or other generators for order 0 elements (integer)
     *
     * The generators' codes are in a freegenes format
     *
     * @return the map of generators (map<generator name, generator code>)
     */
    std::map<std::string, std::vector<int>> get_generators_order_0();

    /**
     * @brief get grammars or other generators for order 1 elements (instructions)
     *
     * The generators' codes are in a freegenes format
     *
     * @return the map of generators (map<generator name, generator code>)
     */
    std::map<std::string, std::vector<int>> get_generators_order_1();

    /**
     * @brief get grammars or other generators for order 2 elements (atomic programs)
     *
     * The generators' codes are in a freegenes format
     *
     * @return the map of generators (map<generator name, generator code>)
     */
    std::map<std::string, std::vector<int>> get_generators_order_2();

public:
    FreeGeneCreationEvoX();

    void init() override;

    void launch() override;

    sp_evox get_base_algo(std::string name);
    sp_univ_evo_algos get_universe(sp_evox algo);

    /**
     * @brief provide the algo the functions needed for the experiment
     */
    void provide_experiment_functions(sp_univ_evo_algos universe, sp_evox algo);

    /**
     * @brief run the experiment
     */
    void exec(sp_univ_evo_algos universe, sp_evox algo);
};

typedef std::shared_ptr<FreeGeneCreationEvoX> sp_experiment_evox_fgc;