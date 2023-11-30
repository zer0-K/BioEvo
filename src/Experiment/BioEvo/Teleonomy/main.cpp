#include <iostream>

#include "ExperimentRunnerTeleonomy.hpp"

int main(int argc, char* argv[])
{
    sp_experiment_runner_teleonomy experiment_runner = std::make_shared<ExperimentRunnerTeleonomy>();

    experiment_runner->init();
    experiment_runner->launch();

    return 0;
}