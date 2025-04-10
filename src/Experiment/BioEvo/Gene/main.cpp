#include <iostream>

#include "ExperimentRunnerGenes.hpp"

int main(int argc, char* argv[])
{
    sp_experiment_runner_phenotypic_body experiment_runner = std::make_shared<ExperimentRunnerGenes>();

    experiment_runner->init();
    experiment_runner->launch();

    return 0;
}