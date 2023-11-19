#pragma once

#include "../../../../Experiment.hpp"

class EvoXDriveTrait : public Experiment
{
protected:


public:
    EvoXDriveTrait();

    void init() override;

    void launch() override;
};

typedef std::shared_ptr<EvoXDriveTrait> sp_experiment_trait_evox;