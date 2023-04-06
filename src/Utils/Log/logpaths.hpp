#pragma once

#include <string>
#include <map>

const std::string EXPERIMENT_CLASSICAL_ALGO_1 = "experiment classical algos 1";

// the paths begin at the root
std::map<const std::string, std::string> pathsmap = {
    { EXPERIMENT_CLASSICAL_ALGO_1 , "log/experiments/classical_algos" }
};
