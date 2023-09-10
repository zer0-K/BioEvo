#include "ExperimentRunnerMaths.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    sp_experiment_runner_maths exp_runner = std::make_shared<ExperimentRunnerMaths>();

    exp_runner->init();
    exp_runner->launch();

    return 0;
}