#pragma once

#include "Experiment.hpp"

/// @brief experiment 2
class Experiment2 : public Experiment
{
protected:
    /// @see Experiment
    void initCodeEaters() override;

public:
    /**
     * @brief Constructor
    */
    Experiment2();

    /// @see Experiment
    void launch() override;
};