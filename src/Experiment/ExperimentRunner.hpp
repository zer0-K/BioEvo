#pragma once

#include <vector>

#include "Experiment.hpp"

class ExperimentRunner
{
private:
    std::vector<sp_experiment> experiments;    ///< experiments

public:
    /**
     * @brief Constructor
    */
    ExperimentRunner(std::vector<sp_experiment> experiments);

    /**
     * @brief Display experiments to choose
    */
    void display_and_launch();
};
