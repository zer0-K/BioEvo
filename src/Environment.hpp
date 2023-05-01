#pragma once

#include "Flow.hpp"
#include <string>
#include <boost/json.hpp>

/// @brief environment
class Environment
{
protected:
    std::string name;   ///< name of the environment

    int number_of_epochs;   ///< number of epochs for evolution

    Flow* input;    ///< input of the environment
    Flow* output;   ///< output of the environment

    /**
     * setters
    */
    void set_output(Flow* ouput);

public:
    /**
     * @brief Constructor
     * 
     * @param[in] name name of the environment
    */
    Environment(std::string name);

    /**
     * @brief Constructor
     * 
     * @param[in] name name of the environment
     * @param[in] nb_epochs_evo number of epochs for evolution
    */
    Environment(std::string name, int nb_epochs_evo);

    
    /**
    * @brief Perform the computation, making the environment evolve according to the laws we define
    * 
    * @param[in] nb_inviduals number of individuals of the current generation
    * @param[in] nb_epochs number of epochs for these individuals
    */
    virtual void evolve(int nb_individuals, int nb_epochs[]) = 0;

    /**
    * @brief Creates the initial output of the environment to feed the first generation of individuals 
    * 
    * @param[in] nb_inviduals number of individuals of the current generation
    * @param[in] nb_epochs number of epochs for these individuals
    */
    virtual void init(int nb_individuals, int nb_epochs[]) = 0;

    /**
     * @brief Compute some values for the individual
     * 
     * The values computes are stored in the environment output
     * 
     * @param[in] nb_individuals number of individuals
     * @param[in] nb_vals number of values to compute for the individuals
    */
    virtual void compute(int nb_individuals, int nb_vals) = 0;

    
    //----- getters
    std::string get_name();
    Flow* get_output();

    //----- setters
    void set_input(Flow* input);

    //----- other
    std::string to_string();
    boost::json::object to_json();
    std::string is_ready();
}; 

