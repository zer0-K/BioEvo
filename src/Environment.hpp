#pragma once

#include "Flow.hpp"
#include <string>

/// @brief environment
class Environment
{
protected:
    std::string name;   ///< name of the environment

    Flow* input;    ///< input of the environment
    Flow* output;   ///< output of the environment

public:
    /**
     * @brief Constructor
     * 
     * @param[in] name name of the environment
    */
    Environment(std::string name);

    
    /**
    * @brief Perform the computation, making the environment evolve according to the laws we define
    */
    virtual void evolve() = 0;

    
    /**
     * getters
    */
    std::string get_name();
    Flow* get_output();

    /**
     * setters
    */
    void set_input(Flow* input);
}; 

