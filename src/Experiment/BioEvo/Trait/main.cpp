#include <iostream>

#include "ExperimentRunnerTraits.hpp"

int main(int argc, char* argv[])
{
    sp_experiment_runner_traits experiment_runner = std::make_shared<ExperimentRunnerTraits>();

    experiment_runner->init();
    experiment_runner->launch();

    return 0;
}