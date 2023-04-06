#pragma once

#include "../../ExperimentOld.hpp"
#include "../UniverseCodeEater.hpp"
#include "../Computing/EatingProcessor.hpp"

/// @brief ExperimentOldCodeEater abstract class
class ExperimentOldCodeEater : ExperimentOld
{
protected:
    //UniverseCodeEater* universeCodeEater; ///< UniverseCodeEater of the ExperimentOldCodeEater
    CodeEater*** code_eaters;   ///< code eaters of the UniverseCodeEater
    EatingProcessor* eating_processor;   ///< eating process (need to be defined at each ExperimentOldCodeEater)

    /**
     * @brief Init the code eaters, is called at the end of the constructor
    */
    virtual void initExperimentOld() = 0;

public:
    /**
     * @brief Constructor
    */
    ExperimentOldCodeEater();

    /**
     * @brief Constructor
     * 
     * @param width width of the UniverseCodeEater of the ExperimentOldCodeEater
     * @param height height of the UniverseCodeEater of the ExperimentOldCodeEater
    */
    ExperimentOldCodeEater(const int width, const int height);

    /**
     * @brief Launch the ExperimentOldCodeEater
    */
    virtual void launch() = 0;

    /**
     * @brief Show the universe
    */
    void show();

    /**
     * @see ExperimentOld
    */
    void loop() override;
};