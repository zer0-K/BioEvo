#pragma once

#include <string>
#include "Flow.hpp"

/// @brief algorithm, as an individual
class Individual
{
private:
    Flow* input;    ///< input of the individual
    Flow* output;   ///< output of the individual

    std::string name;   ///< name of the individual

public:
    /**
     * @brief Constructor
     * 
     * @param[in] name name of the individual
    */
    Individual(std::string name);

   /**
    * @brief Perform the computation, making the individual evolve according to the laws we define
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