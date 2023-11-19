#pragma once

#include "../../ExperimentRunner.hpp"

#include "EvoAlgos/EvoX/EvoXDriveTrait.hpp"

#include <iostream>

class ExperimentRunnerTraits : public ExperimentRunner
{
public:
    ExperimentRunnerTraits();

    void init() override;
};

ExperimentRunnerTraits::ExperimentRunnerTraits()
    : ExperimentRunner(name_exp_bioevo_traits)
{}

void ExperimentRunnerTraits::init()
{
    experiments = {
        std::make_shared<EvoXDriveTrait>()
    };

    for(int i=0;i<experiments.size();i++)
    {
        experiments[i]->init();
    }
}

typedef std::shared_ptr<ExperimentRunnerTraits> sp_experiment_runner_traits;