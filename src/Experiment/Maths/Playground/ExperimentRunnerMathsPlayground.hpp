#pragma once

#include "../../ExperimentRunner.hpp"

#include "BasicOps/GenerationRecursiveOps.hpp"

#include <iostream>

class ExperimentRunnerMathsPlayground : public ExperimentRunner
{
public:
    ExperimentRunnerMathsPlayground();

    void init() override;
};

ExperimentRunnerMathsPlayground::ExperimentRunnerMathsPlayground()
    : ExperimentRunner(name_exp_maths_playground)
{}

void ExperimentRunnerMathsPlayground::init()
{
    experiments = {
        std::make_shared<GenerationRecursiveOps>()
    };

    for(int i=0;i<experiments.size();i++)
    {
        experiments[i]->init();
    }
}

typedef std::shared_ptr<ExperimentRunnerMathsPlayground> sp_experiment_runner_maths_playground;