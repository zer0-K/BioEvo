#include <iostream>

#include "ExperimentRunnerMathsPlayground.hpp"

int main(int argc, char* argv[])
{
    sp_experiment_runner_maths_playground experiment_runner = std::make_shared<ExperimentRunnerMathsPlayground>();

    experiment_runner->init();
    experiment_runner->launch();

    return 0;
}