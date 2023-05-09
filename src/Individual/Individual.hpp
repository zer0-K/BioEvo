#pragma once

#include "../Entity.hpp"
#include "../Flow/Flow.hpp"

/// @brief algorithm, as an individual
class Individual : public Entity
{
protected:
    std::shared_ptr<Flow> input;    ///< input of the individual
    std::shared_ptr<Flow> output;   ///< output of the individual

    int number_of_epochs;   ///< number of epochs for learning
    
    /**
     * setters
    */
    void set_output(std::shared_ptr<Flow> ouput);

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
     * @brief @see Entity constructor
    */
    Individual(boost::json::object params);

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
    virtual std::shared_ptr<Flow> compute(std::shared_ptr<Flow> x)=0;

    //----- getters
    std::shared_ptr<Flow> get_output();

    //----- setters
    void set_input(std::shared_ptr<Flow> input);
    void set_number_of_epochs(int nb_epoch_learn);

    //----- other
    boost::json::object object_to_json() override;
    virtual std::string to_string();
    virtual std::string is_ready();

    static boost::json::object type_to_json()
    {
        return Entity::type_to_json();
    }
};

typedef std::shared_ptr<Individual> sp_individual;