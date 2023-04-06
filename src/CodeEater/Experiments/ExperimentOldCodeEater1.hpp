#pragma once

#include "ExperimentOldCodeEater.hpp"

/// @brief ExperimentOldCodeEater 1
class ExperimentOldCodeEater1 : public ExperimentOldCodeEater
{
protected:
    /// @see ExperimentOldCodeEater
    void initExperimentOld() override;

public:
    /**
     * @brief Constructor
    */
    ExperimentOldCodeEater1();

    /// @see ExperimentOldCodeEater
    void launch() override;
};