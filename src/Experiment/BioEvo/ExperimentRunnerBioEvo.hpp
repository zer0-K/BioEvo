#pragma once

#include "Trait/ExperimentRunnerTraits.hpp"
#include "Gene/ExperimentRunnerGenes.hpp"
#include "Replicators/ExperimentRunnerReplicators.hpp"

#include <iostream>

class ExperimentRunnerBioEvo : public ExperimentRunner
{
public:
    ExperimentRunnerBioEvo();

    void init() override;
};

ExperimentRunnerBioEvo::ExperimentRunnerBioEvo()
    : ExperimentRunner(name_exp_bioevo)
{}

void ExperimentRunnerBioEvo::init()
{
    experiments = {
        std::make_shared<ExperimentRunnerTraits>(),
        std::make_shared<ExperimentRunnerGenes>(),
        std::make_shared<ExperimentRunnerReplicators>()
    };

    for(int i=0;i<experiments.size();i++)
    {
        experiments[i]->init();
    }
}

typedef std::shared_ptr<ExperimentRunnerBioEvo> sp_experiment_runner_bioevo;