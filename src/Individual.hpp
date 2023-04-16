#pragma once

#include <string>
#include "Flow.hpp"

/// @brief algorithm, as an individual
class Individual
{
protected:
    Flow* input;    ///< input of the individual
    Flow* output;   ///< output of the individual

    std::string name;   ///< name of the individual

    int number_of_epochs;   ///< number of epochs for learning
    
    /**
     * setters
    */
    void set_output(Flow* ouput);

public:
    /**
     * @brief Constructor
     * 
     * @param[in] name name of the individual
    */
    Individual(std::string name);
    
    /**
     * @brief Constructor
     * 
     * @param[in] name name of the individual
     * @param[in] nb_epoch_learn number of epochs for learning
    */
    Individual(std::string name, int nb_epch_learn);

   /**
    * @brief Perform the computation, making the individual evolve according to the laws we define
    */
    virtual void evolve() = 0;

    /**
     * @brief Compute f(x) given a x
     * 
     * @param[in] x x
     * 
     * @return f(x)
    */
    virtual Flow* compute(Flow* x)=0;

    //----- getters
    std::string get_name();
    Flow* get_output();

    //----- setters
    void set_input(Flow* input);
    void set_number_of_epochs(int nb_epoch_learn);

    //----- other
    std::string to_string();
};