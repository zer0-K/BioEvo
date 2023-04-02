#pragma once

#include "Experiment.hpp"

/// @brief experiment 3
class Experiment3 : public Experiment
{
protected:
    /// @see Experiment
    void initCodeEaters() override;

public:
    /**
     * @brief Constructor
    */
    Experiment3();

    /// @see Experiment
    void launch() override;
};