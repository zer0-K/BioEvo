#include <iostream>

#include "ExperimentRunnerReplicators.hpp"

int main(int argc, char* argv[])
{
    sp_experiment_runner_replicators experiment_runner = std::make_shared<ExperimentRunnerReplicators>();

    experiment_runner->init();
    experiment_runner->launch();

    return 0;
}