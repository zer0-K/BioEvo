#include <iostream>

#include "ExperimentRunnerGenesis.hpp"

int main(int argc, char* argv[])
{
    sp_experiment_runner_genesis experiment_runner = std::make_shared<ExperimentRunnerGenesis>();

    experiment_runner->init();
    experiment_runner->launch();

    return 0;
}