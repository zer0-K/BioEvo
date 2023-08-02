#include "ExperimentRunnerEvoAlgos.hpp"

int main(int argc, char* argv[])
{
    sp_experiment_runner_evoalgos exp_runner = std::make_shared<ExperimentRunnerEvoAlgos>();

    exp_runner->init();
    exp_runner->launch();

    return 0;
}