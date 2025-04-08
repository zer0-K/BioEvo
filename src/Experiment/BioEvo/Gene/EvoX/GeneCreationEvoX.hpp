#pragma once

#include <map>

#include "../../../Experiment.hpp"

#include "../../../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/EvoX.hpp"


class GeneCreationEvoX : public Experiment
{
protected:
    uint max_nb_instr_exec;

public:
    GeneCreationEvoX();

    void init() override;

    void launch() override;

    /// @brief check that the base algo can self-compile
    bool check_base_algo();
    sp_evox get_base_algo(int step);
    //void build_new_algo_artificially(sp_evox base_alg, std::string file_nameo);
    sp_univ_evo_algos get_universe(sp_evox algo);

    //-------------------- step 1

    //std::vector<int> get_DNA_step_1();

    /// @brief first step
    void exec_step_1(sp_univ_evo_algos universe, sp_evox algo);

};
