#pragma once

#include "../Entity.hpp"
#include "../Biology/QuantumData/QuantumDataAbstract.hpp"

/// @brief algorithm, as an individual
class Individual : public Entity
{
public:
    /**
     * @brief Constructor
     * 
     * @param[in] name name of the individual
    */
    Individual(std::string name);

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
    virtual QuantumDataAbstract compute(QuantumDataAbstract x)=0;

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