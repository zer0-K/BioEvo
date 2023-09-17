#include <iostream>

#include "ExperimentRunnerFunctionExecution.hpp"

int main(int argc, char* argv[])
{
    sp_experiment_runner_func_exec experiment_runner = std::make_shared<ExperimentRunnerFunctionExecution>();

    experiment_runner->init();
    experiment_runner->launch();

    return 0;
}