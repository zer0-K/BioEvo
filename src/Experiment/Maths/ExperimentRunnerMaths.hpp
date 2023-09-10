#pragma once

#include "Playground/ExperimentRunnerMathsPlayground.hpp"

#include <iostream>

class ExperimentRunnerMaths : public ExperimentRunner
{
public:
    ExperimentRunnerMaths();

    void init() override;
};

ExperimentRunnerMaths::ExperimentRunnerMaths()
    : ExperimentRunner(name_exp_maths)
{}

void ExperimentRunnerMaths::init()
{
    experiments = {
        std::make_shared<ExperimentRunnerMathsPlayground>()
    };

    for(int i=0;i<experiments.size();i++)
    {
        experiments[i]->init();
    }
}

typedef std::shared_ptr<ExperimentRunnerMaths> sp_experiment_runner_maths;