#include "ExperimentRunnerClassicalInfo.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    sp_experiment_runner_classical_info exp_runner = std::make_shared<ExperimentRunnerClassicalInfo>();

    exp_runner->init();
    exp_runner->launch();

    return 0;
}