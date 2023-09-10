#pragma once

#include "../../../Experiment/ExperimentRunner.hpp"

#include "../../../Experiment/BioEvo/Replicators/EvoAlgos/EvoX/ReplicationEvoXQuine.hpp"

#include <iostream>

class ExperimentRunnerEvoAlgos : public ExperimentRunner
{
public:
    ExperimentRunnerEvoAlgos();

    void init() override;
};

ExperimentRunnerEvoAlgos::ExperimentRunnerEvoAlgos()
    : ExperimentRunner(name_exp_evoalgos)
{}

void ExperimentRunnerEvoAlgos::init()
{
    experiments = {
        std::make_shared<ReplicationEvoXQuine>()
    };


    for(int i=0;i<experiments.size();i++)
    {
        experiments[i]->init();
    }
}

typedef std::shared_ptr<ExperimentRunnerEvoAlgos> sp_experiment_runner_evoalgos;