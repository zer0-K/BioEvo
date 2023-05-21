#include "EnvironmentClassical.hpp"

#include "../Declaration/PreprocessingDefinitions.hpp"
#include "../Declaration/Constants.hpp"
#include "../Utils/Log/Logger.hpp"

EnvironmentClassical::EnvironmentClassical(std::string name, size_t size_test, size_t size_validation)
    :Environment::Environment(name, size_test+size_validation)
{
    this->size_test = size_test;
    this->size_validation = size_validation;
}

EnvironmentClassical::EnvironmentClassical(boost::json::object params)
    :Environment::Environment(params)
{
    // set sizes
    boost::json::value* jsize_test = params.if_contains("size_test");
    boost::json::value* jsize_validation = params.if_contains("size_validation");

    if(jsize_test != nullptr && jsize_validation != nullptr)
    {
        this->size_test = boost::json::value_to<size_t>(*jsize_test);
        this->size_validation = boost::json::value_to<size_t>(*jsize_validation);

       env_values = std::vector<QuantumDataAbstract>(size_test + size_validation);
    }
}

std::string EnvironmentClassical::to_string()
{
    std::string res = Environment::to_string();

    res += ", size_test : " + std::to_string(size_test);
    res += ", size_validation : " + std::to_string(size_validation);

    return res;
}

boost::json::object EnvironmentClassical::object_to_json()
{
    boost::json::object jenv = Environment::object_to_json();

    jenv["size_test"] = size_test;
    jenv["size_validation"] = size_validation;

    return jenv;
}
