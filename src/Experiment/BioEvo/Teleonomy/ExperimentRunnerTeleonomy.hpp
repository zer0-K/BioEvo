#pragma once

#include "../../ExperimentRunner.hpp"

#include "EvoX/EvoXTeleonomicalDesign.hpp"

#include <iostream>

class ExperimentRunnerTeleonomy : public ExperimentRunner
{
public:
    ExperimentRunnerTeleonomy();

    void init() override;
};

ExperimentRunnerTeleonomy::ExperimentRunnerTeleonomy()
    : ExperimentRunner(name_exp_bioevo_teleonomy)
{}

void ExperimentRunnerTeleonomy::init()
{
    experiments = {
        std::make_shared<EvoXTeleonomicalDesign>()
    };

    for(int i=0;i<experiments.size();i++)
    {
        experiments[i]->init();
    }
}

typedef std::shared_ptr<ExperimentRunnerTeleonomy> sp_experiment_runner_teleonomy;