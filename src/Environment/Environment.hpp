#pragma once

#include <string>
#include <vector>

#include "../Entity.hpp"
#include "../Biology/QuantumData/QuantumDataAbstract.hpp"

/// @brief environment
class Environment : public Entity
{
protected:
    /**
     * @brief Values of the environment
     * 
     * The environment is constitued of a list of values,
     * which can be split between test and validation data
    */
    std::vector<QuantumDataAbstract> env_values;

public:
    /**
     * @brief Constructor
     * 
     * @param[in] name name of the environment
     * @param[in] size size of the environment
    */
    Environment(std::string name, size_t size);

    /**
     * @brief @see Entity constructor
    */
    Environment(boost::json::object params);
    
    /**
    * @brief Perform the computation, making the environment evolve according to the laws we define
    */
    virtual void evolve() = 0;

    /**
     * @brief Init the values
     */
    virtual void init_values() = 0;

    
    //----- other
    std::string to_string();
    boost::json::object object_to_json() override;
    std::string is_ready();

    static boost::json::object type_to_json()
    {
        return Entity::type_to_json();
    }
}; 

typedef std::shared_ptr<Environment> sp_environment;