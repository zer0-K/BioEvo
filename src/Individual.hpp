#pragma once

#include "Flow.hpp"

/// @brief algorithm, as an individual
class Individual
{
private:
    Flow* input;    ///< input of the individual
    Flow* output;   ///< output of the individual

public:
    /**
     * @brief Constructor
    */
    Individual();

    /**
     * @brief set input of the individual
     * 
     * @param[in] input input to set to the individual
    */
    void set_input(Flow* input);

    /**
     * @brief get output of the individual
     * 
     * @return output of the individual
    */
    Flow* get_output();

    /**
    * @brief Perform the computation, making the individual evolve according to the laws we define
    */
    virtual void evolve() = 0;
};