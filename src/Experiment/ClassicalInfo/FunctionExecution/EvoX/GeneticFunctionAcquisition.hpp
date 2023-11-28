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

    sp_evox get_algo();

    /**
     * @brief get the genes for the free genes
     *
     * The free genes represent the function that writes 
     * another function on a certain place
     */
    std::vector<int> get_genes_function_write();

    void FreeGenesFunctionRead(sp_evox algo);
    void FreeGenesFunctionWrite(sp_evox algo);
};

typedef std::shared_ptr<GeneticFunctionAcquisition> sp_experiment_func_acquisition;