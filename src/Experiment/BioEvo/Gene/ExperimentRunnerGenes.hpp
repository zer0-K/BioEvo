#pragma once

#include "../../ExperimentRunner.hpp"

#include "EvoX/FreeGeneCreationEvoX.hpp" 

#include <iostream>

class ExperimentRunnerGenes : public ExperimentRunner
{
public:
    ExperimentRunnerGenes();

    void init() override;
};

ExperimentRunnerGenes::ExperimentRunnerGenes()
    : ExperimentRunner(name_exp_bioevo_genes)
{}

void ExperimentRunnerGenes::init()
{
    experiments = {
        std::make_shared<FreeGeneCreationEvoX>()
    };

    for(int i=0;i<experiments.size();i++)
    {
        experiments[i]->init();
    }
}

typedef std::shared_ptr<ExperimentRunnerGenes> sp_experiment_runner_genes;