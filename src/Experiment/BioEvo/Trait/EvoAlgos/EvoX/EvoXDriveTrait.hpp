#pragma once

#include "../../../../Experiment.hpp"

#include "../../../../../Models/EvoAlgos/X86Algo/EvoX.hpp"

class EvoXDriveTrait : public Experiment
{
protected:


public:
    EvoXDriveTrait();

    void init() override;

    void launch() override;

    sp_evox get_algo(std::string name);

    void test_setup();
};

typedef std::shared_ptr<EvoXDriveTrait> sp_experiment_trait_evox;