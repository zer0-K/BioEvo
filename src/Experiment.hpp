#pragma once

#include "Universe.hpp"

/// @brief experiment abstract class
class Experiment
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
    Experiment();

    /**
     * @brief Constructor
     * 
     * @param width width of the universe of the experiment
     * @param height height of the universe of the experiment
    */
    Experiment(const int width, const int height);

    /**
     * @brief Launch the experiment
    */
    virtual void launch() = 0;

    /**
     * @brief Loop to make time go on 
    */
    virtual void loop();
};