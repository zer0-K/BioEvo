#pragma once

#include <map>

#include "../../../Experiment.hpp"

#include "../../../../Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp"
#include "../../../../Models/EvoAlgos/X86Algo/EvoX.hpp"

class GeneToProgtein : public Experiment
{
protected:

public:
    GeneToProgtein();

    void init() override;

    void launch() override;

    sp_evox get_base_algo();
    sp_univ_evo_algos get_universe(sp_evox algo);

    /// @brief provide the heaviside function needed for the experiment
    std::vector<int> get_heaviside();

    /// @brief provide ribosome
    std::vector<int> get_ribosome();

    std::map<std::string, std::vector<int>> get_tRNAs_1();
    
    /// @brief first step : example function : heaviside
    void exec_step_1(sp_univ_evo_algos universe, sp_evox algo);

    /// @brief second step : some tRNAs
    void exec_step_2(sp_univ_evo_algos universe, sp_evox algo);

    /// @brief third step : ribosome and RNAi
    void exec_step_3(sp_univ_evo_algos universe, sp_evox algo);
};

typedef std::shared_ptr<GeneToProgtein> sp_experiment_evox_gtp;