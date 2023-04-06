#pragma once

#include "ExperimentCodeEater.hpp"

/// @brief ExperimentCodeEater 3
class ExperimentCodeEater3 : public ExperimentCodeEater
{
protected:
    /// @see ExperimentCodeEater
    void initExperiment() override;

public:
    /**
     * @brief Constructor
    */
    ExperimentCodeEater3();

    /// @see ExperimentCodeEater
    void launch() override;
};