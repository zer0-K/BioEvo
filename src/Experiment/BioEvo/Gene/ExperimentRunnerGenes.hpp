#pragma once

#include "../../ExperimentRunner.hpp"

#include "EvoX/FreeMoleculesCreationEvoX.hpp" 
#include "EvoX/GeneToProgtein.hpp" 
//#include "EvoX/GeneCreationEvoX.hpp"

#include <iostream>

class ExperimentRunnerGenes : public ExperimentRunner
{
public:
    ExperimentRunnerGenes();

    void init() override;
};

ExperimentRunnerGenes::ExperimentRunnerGenes()
    : ExperimentRunner(name_exp_bioevo_phenotypic_body)
{}

void ExperimentRunnerGenes::init()
{
    experiments = {
        std::make_shared<FreeMoleculesCreationEvoX>(),
        std::make_shared<GeneToProgtein>(),
        //std::make_shared<GeneCreationEvoX>()
    };

    for(int i=0;i<experiments.size();i++)
    {
        experiments[i]->init();
    }
}

typedef std::shared_ptr<ExperimentRunnerGenes> sp_experiment_runner_phenotypic_body;