#pragma once

#include "Universe.hpp"

/// @brief experiment abstract class
class ExperimentOld
{
protected:
    Universe* universe; ///< universe of the experiment

    /**
     * @brief Init the experiment
    */
    virtual void initexperiment() {};

public:
    /**
     * @brief Constructor
    */
    ExperimentOld();

    /**
     * @brief Constructor
     * 
     * @param width width of the universe of the experiment
     * @param height height of the universe of the experiment
    */
    ExperimentOld(const int width, const int height);

    /**
     * @brief Launch the experiment
    */
    virtual void launch() = 0;

    /**
     * @brief Loop to make time go on 
    */
    virtual void loop();
};