#pragma once

#include "../../ExperimentRunner.hpp"

#include "EvoAlgosGenesis/GenerateBaseEvoX1.hpp"
#include "EvoAlgosGenesis/GenerateBaseEvoX2.hpp"

#include <iostream>

class ExperimentRunnerGenesis : public ExperimentRunner
{
public:
    ExperimentRunnerGenesis();

    void init() override;
};

ExperimentRunnerGenesis::ExperimentRunnerGenesis()
    : ExperimentRunner(name_exp_bioevo_genesis)
{}

void ExperimentRunnerGenesis::init()
{
    experiments = {
        std::make_shared<GenerateBaseEvoX1>(),
        std::make_shared<GenerateBaseEvoX2>()
    };

    for(int i=0;i<experiments.size();i++)
    {
        experiments[i]->init();
    }
}

typedef std::shared_ptr<ExperimentRunnerGenesis> sp_experiment_runner_genesis;