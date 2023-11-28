#pragma once

#include "../../../Experiment.hpp"

#include "../../../../Models/EvoAlgos/X86Algo/EvoX.hpp"

class GeneticFunctionAcquisition : public Experiment
{
protected:


public:
    GeneticFunctionAcquisition();

    void init() override;

    void launch() override;

    /// @brief provides algo for FreeGenesFunctionRead
    sp_evox get_algo_read();
    /// @brief provides algo for FreeGenesFunctionWrite
    sp_evox get_algo_write();

    /**
     * @brief get the genes for the free genes
     *
     * The free genes represent the function that writes 
     * another function on a certain place
     */
    std::vector<int> get_genes_function_write();

    void FreeGenesFunctionRead();
    void FreeGenesFunctionWrite();
};

typedef std::shared_ptr<GeneticFunctionAcquisition> sp_experiment_func_acquisition;