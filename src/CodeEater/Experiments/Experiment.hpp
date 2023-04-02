#pragma once

#include "../Universe.hpp"
#include "../Computing/EatingProcessor.hpp"

/// @brief experiment abstract class
class Experiment
{
protected:
    Universe* universe; ///< universe of the experiment
    CodeEater*** code_eaters;   ///< code eaters of the universe
    EatingProcessor* eating_processor;   ///< eating process (need to be defined at each experiment)

    /**
     * @brief Init the code eaters, is called at the end of the constructor
    */
    virtual void initCodeEaters() {};

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
    void loop();
};