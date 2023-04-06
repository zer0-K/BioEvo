#pragma once

#include "ExperimentCodeEater.hpp"

/// @brief ExperimentCodeEater 2
class ExperimentCodeEater2 : public ExperimentCodeEater
{
protected:
    /// @see ExperimentCodeEater
    void initExperiment() override;

public:
    /**
     * @brief Constructor
    */
    ExperimentCodeEater2();

    /// @see ExperimentCodeEater
    void launch() override;
};