#pragma once

#include "FunctionExecution/ExperimentRunnerFunctionExecution.hpp"

#include <iostream>

class ExperimentRunnerClassicalInfo : public ExperimentRunner
{
public:
    ExperimentRunnerClassicalInfo();

    void init() override;
};

ExperimentRunnerClassicalInfo::ExperimentRunnerClassicalInfo()
    : ExperimentRunner(name_exp_classical_info)
{}

void ExperimentRunnerClassicalInfo::init()
{
    experiments = {
        std::make_shared<ExperimentRunnerFunctionExecution>(),
    };

    for(int i=0;i<experiments.size();i++)
    {
        experiments[i]->init();
    }
}

typedef std::shared_ptr<ExperimentRunnerClassicalInfo> sp_experiment_runner_classical_info;