#pragma once

#include "../../../Experiment.hpp"

#include "../../../../Models/EvoAlgos/X86Algo/EvoX.hpp"

class MolecularFunctionAcquisition : public Experiment
{
protected:


public:
    MolecularFunctionAcquisition();

    void init() override;

    void launch() override;

    /// @brief provides algo for FreeMoleculesFunctionRead
    sp_evox get_algo_read();
    /// @brief provides algo for FreeMoleculesFunctionWrite
    sp_evox get_algo_write();

    /**
     * @brief get the molecular body for the free molecules
     *
     * The free molecules represent the function that writes 
     * another function on a certain place
     */
    std::vector<int> get_molecular_body_function_write();

    void FreeMoleculesFunctionRead();
    void FreeMoleculesFunctionWrite();
};

typedef std::shared_ptr<MolecularFunctionAcquisition> sp_experiment_func_acquisition;