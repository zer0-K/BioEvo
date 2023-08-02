#pragma once

#include <vector>

#include "Experiment.hpp"

class ExperimentRunner : public Experiment
{
protected:
    std::vector<sp_experiment> experiments;    ///< experiments

public:
    using Experiment::Experiment;

    /**
     * @brief Display experiments to choose
    */
    void launch() override;
};

typedef std::shared_ptr<ExperimentRunner> sp_experiment_runner;