#include "Experiment.hpp"

Experiment::Experiment(std::string experiment_name)
{
    name = experiment_name;
}

std::string Experiment::get_name()
{
    return name;
}