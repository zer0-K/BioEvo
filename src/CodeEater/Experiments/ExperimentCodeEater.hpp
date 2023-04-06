#pragma once

#include "../../Experiment.hpp"
#include "../UniverseCodeEater.hpp"
#include "../Computing/EatingProcessor.hpp"

/// @brief ExperimentCodeEater abstract class
class ExperimentCodeEater : Experiment
{
protected:
    //UniverseCodeEater* universeCodeEater; ///< UniverseCodeEater of the ExperimentCodeEater
    CodeEater*** code_eaters;   ///< code eaters of the UniverseCodeEater
    EatingProcessor* eating_processor;   ///< eating process (need to be defined at each ExperimentCodeEater)

    /**
     * @brief Init the code eaters, is called at the end of the constructor
    */
    virtual void initExperiment() = 0;

public:
    /**
     * @brief Constructor
    */
    ExperimentCodeEater();

    /**
     * @brief Constructor
     * 
     * @param width width of the UniverseCodeEater of the ExperimentCodeEater
     * @param height height of the UniverseCodeEater of the ExperimentCodeEater
    */
    ExperimentCodeEater(const int width, const int height);

    /**
     * @brief Launch the ExperimentCodeEater
    */
    virtual void launch() = 0;

    /**
     * @brief Show the universe
    */
    void show();

    /**
     * @see Experiment
    */
    void loop() override;
};