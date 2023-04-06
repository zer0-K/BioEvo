#pragma once

#include "PreprocessingDefinitions.hpp"
#include "Buffer.hpp"

/// @brief universe for the experiments
class Universe
{
protected:
    int width;  ///< width of the universe
    int height; ///< height of the universe

    int number_of_individuals;      ///< current number of individuals in the universe
    int max_number_of_individuals;  ///< maximum number of individuals in the universe

    Individual** individuals;   ///< individuals living in the universe
    Environment* environment;   ///< environment with which the individual interacts
    Buffer* buffer;             ///< buffer, to feed individual's input with environment's output and vice-vesra

    int t;  ///< time

    bool state; ///< universe state

    /**
     * @brief Proceed to the next step
    */
    virtual void nextStep();

public:

    /**
     * @brief Constructor
    */
    Universe();
    
    /**
     * @brief Constructor
     * 
     * @param[in] width width of the universe
     * @param[in] height height of the universe
    */
    Universe(const int width, const int height);

    /**
     * @brief Destructor
    */
    ~Universe();

    /**
     * @brief Show the universe
    */
    virtual void show()=0;

    /**
     * @brief Proceed to the next steps
     * 
     * @param nb_steps number of steps
    */
    virtual void nextSteps(int nb_steps);

    //----- getters
    int getWidth();
    int getHeight();
};