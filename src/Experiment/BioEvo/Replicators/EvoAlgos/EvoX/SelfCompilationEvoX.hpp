#pragma once

#include <map>

#include "../../../../Experiment.hpp"

#include "../../../../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"
#include "../../../../../Models/EvoAlgos/X86Algo/EvoX.hpp"


class SelfCompilationEvoX : public Experiment
{
protected:

public:
    SelfCompilationEvoX();

    void init() override;

    void launch() override;

    sp_evox get_base_algo();
    sp_univ_evo_algos get_universe(sp_evox algo);

    //-------------------- step 1

    std::vector<int> get_DNA_step_1();

    /// @brief first step
    void exec_step_1(sp_univ_evo_algos universe, sp_evox algo);
};

typedef std::shared_ptr<SelfCompilationEvoX> sp_experiment_evox_selfc;