#include "ExperimentRunnerBioEvo.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    sp_experiment_runner_bioevo exp_runner = std::make_shared<ExperimentRunnerBioEvo>();

    exp_runner->init();
    exp_runner->launch();

    return 0;
}