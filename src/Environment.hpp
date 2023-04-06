#pragma once

#include "Flow.hpp"

class Environment
{
private:
    Flow* input;    ///< input of the environment
    Flow* output;   ///< output of the environment

public:
    /**
     * @brief Constructor
    */
    Environment();

    /**
     * @brief set input of the individual
     * 
     * @param[in] input input to set to the environment
    */
    void set_input(Flow* input);

    /**
     * @brief get output of the environment
     * 
     * @return output of the environment
    */
    Flow* get_output();

    /**
    * @brief Perform the computation, making the environment evolve according to the laws we define
    */
    virtual void evolve() = 0;
};

