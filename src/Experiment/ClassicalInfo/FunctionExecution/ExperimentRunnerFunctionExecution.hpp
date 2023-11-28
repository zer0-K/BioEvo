#pragma once

#include "../../ExperimentRunner.hpp"

#include "EvoX/FunctionExecutionEvoX.hpp"
#include "EvoX/GeneticFunctionAcquisition.hpp"

#include <iostream>

class ExperimentRunnerFunctionExecution : public ExperimentRunner
{
public:
    ExperimentRunnerFunctionExecution();

    void init() override;
};

ExperimentRunnerFunctionExecution::ExperimentRunnerFunctionExecution()
    : ExperimentRunner(name_exp_classical_info_func_exec)
{}

void ExperimentRunnerFunctionExecution::init()
{
    experiments = {
        std::make_shared<FunctionExecutionEvoX>(),
        std::make_shared<GeneticFunctionAcquisition>()
    };

    for(int i=0;i<experiments.size();i++)
    {
        experiments[i]->init();
    }
}

typedef std::shared_ptr<ExperimentRunnerFunctionExecution> sp_experiment_runner_func_exec;