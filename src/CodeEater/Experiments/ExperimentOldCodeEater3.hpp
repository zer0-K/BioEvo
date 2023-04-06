#pragma once

#include "ExperimentOldCodeEater.hpp"

/// @brief ExperimentOldCodeEater 3
class ExperimentOldCodeEater3 : public ExperimentOldCodeEater
{
protected:
    /// @see ExperimentOldCodeEater
    void initExperimentOld() override;

public:
    /**
     * @brief Constructor
    */
    ExperimentOldCodeEater3();

    /// @see ExperimentOldCodeEater
    void launch() override;
};