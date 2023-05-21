#pragma once

#include "Environment.hpp"

/// @brief environment
class EnvironmentClassical : public Environment 
{
protected:
    size_t size_test;   ///< size of test data
    size_t size_validation; ///< size of validation data

public:
    /**
     * @brief Constructor
     * 
     * @param[in] name name of the environment
     * @param[in] size_test size of test data
     * @param[in] size_validation size of validation data
     */
    EnvironmentClassical(std::string name, size_t size_test, size_t size_validation);

    /// @brief @see Environment constructor
    EnvironmentClassical(boost::json::object params);
    
    //----- other
    std::string to_string();
    boost::json::object object_to_json() override;
}; 

typedef std::shared_ptr<EnvironmentClassical> sp_environment_classical;