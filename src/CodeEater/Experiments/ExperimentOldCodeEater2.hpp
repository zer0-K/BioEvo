#pragma once

#include "ExperimentOldCodeEater.hpp"

/// @brief ExperimentOldCodeEater 2
class ExperimentOldCodeEater2 : public ExperimentOldCodeEater
{
protected:
    /// @see ExperimentOldCodeEater
    void initExperimentOld() override;

public:
    /**
     * @brief Constructor
    */
    ExperimentOldCodeEater2();

    /// @see ExperimentOldCodeEater
    void launch() override;
};