#pragma once

#include "ExperimentCodeEater.hpp"

/// @brief ExperimentCodeEater 1
class ExperimentCodeEater1 : public ExperimentCodeEater
{
protected:
    /// @see ExperimentCodeEater
    void initExperiment() override;

public:
    /**
     * @brief Constructor
    */
    ExperimentCodeEater1();

    /// @see ExperimentCodeEater
    void launch() override;
};