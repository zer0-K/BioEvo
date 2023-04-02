#pragma once

#include "Experiment.hpp"

/// @brief experiment 1
class Experiment1 : public Experiment
{
protected:
    /// @see Experiment
    void initCodeEaters() override;

public:
    /**
     * @brief Constructor
    */
    Experiment1();

    /// @see Experiment
    void launch() override;
};