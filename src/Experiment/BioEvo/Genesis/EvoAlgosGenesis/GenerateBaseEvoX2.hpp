#pragma once

#include <map>

#include "../../../Experiment.hpp"

#include "../../../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/EvoX.hpp"

class GenerateBaseEvoX2 : public Experiment
{
protected:


public:
    GenerateBaseEvoX2();

    void init() override;

    void launch() override;

    sp_evox get_base_evox();

    std::map<std::string, std::vector<int>> get_utility_generators();
    std::map<std::string, std::vector<int>> get_generators_order_0();
    std::map<std::string, std::vector<int>> get_generators_order_1();
    std::map<std::string, std::vector<int>> get_genome_parts();

    sp_univ_evo_algos get_evox_universe(sp_evox algo);
    void trigger_synthesis(sp_evox algo, sp_univ_evo_algos universe);
};

typedef std::shared_ptr<GenerateBaseEvoX2> sp_experiment_genesis_baseevox_2;