#pragma once

#include <memory>
#include <string>

#include "../Universe/Universe.hpp"

class Experiment
{
protected:
    std::string name;   ///< experiment name

    sp_universe universe;

public:
    /// @brief Constructor
    Experiment(std::string experiment_name);

    /**
     * @brief Init the experiment
    */
    virtual void init()=0;

    /**
     * @brief Launch the experiment
    */
    virtual void launch()=0;

    //----- getters

    std::string get_name();
};

typedef std::shared_ptr<Experiment> sp_experiment;