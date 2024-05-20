#pragma once

#include "../../ExperimentRunner.hpp"

#include "EvoAlgos/EvoX/ReplicationEvoXQuine.hpp"
#include "EvoAlgos/EvoX/SelfCompilationEvoX.hpp"

#include <iostream>

class ExperimentRunnerReplicators : public ExperimentRunner
{
public:
    ExperimentRunnerReplicators();

    void init() override;
};

ExperimentRunnerReplicators::ExperimentRunnerReplicators()
    : ExperimentRunner(name_exp_bioevo_replication)
{}

void ExperimentRunnerReplicators::init()
{
    experiments = {
        std::make_shared<ReplicationEvoXQuine>(),
        std::make_shared<SelfCompilationEvoX>()
    };

    for(int i=0;i<experiments.size();i++)
    {
        experiments[i]->init();
    }
}

typedef std::shared_ptr<ExperimentRunnerReplicators> sp_experiment_runner_replicators;