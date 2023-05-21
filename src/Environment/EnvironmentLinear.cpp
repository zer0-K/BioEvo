#include "EnvironmentLinear.hpp"

#include <cstdlib>
#include <vector>
#include <iostream>

#include "../Declaration/PreprocessingDefinitions.hpp"
#include "../Declaration/Constants.hpp"
#include "../Utils/Log/Logger.hpp"
#include "../Utils/Convert/tostring.hpp"
#include "../Biology/QuantumData/TestData.hpp"
#include "../Biology/QuantumData/ValidationData.hpp"

EnvironmentLinear::EnvironmentLinear(std::string name, size_t size_test, size_t size_validation, int dimension, std::vector<double> w, double b)
    :EnvironmentClassical::EnvironmentClassical(name, size_test, size_validation)
{
    logger_write(2, FLAG_INIT + "Creating linear model environment...");

    this->dimension = dimension;
    this->w = w;
    this->b = b;

    logger_write(2,FLAG_INIT + name + " created. Linear model dimension : " + std::to_string(dimension) \
        + ", weights : " + convert_str(w) +", biases : " + std::to_string(b));
}

EnvironmentLinear::EnvironmentLinear(boost::json::object params)
    :EnvironmentClassical::EnvironmentClassical(params)
{
    boost::json::value* jdim = params.if_contains("dimension");
    boost::json::value* jweights = params.if_contains("weights");
    boost::json::value* jbias = params.if_contains("bias");

    // dimension
    if(jdim != nullptr)
        dimension = boost::json::value_to<int>(*jdim);
    else
        dimension = INDIV_LINEAR_DEFAULT_DIMENSION;

    // bias
    if(jbias != nullptr)
        b = boost::json::value_to<double>(*jbias);
    else
        b = INDIV_LINEAR_DEFAULT_BIAS;

    // weights
    w = std::vector<double>(dimension);
    if(jweights != nullptr && jweights->if_array() != nullptr)
    {
        boost::json::array* arr_weights = jweights->if_array(); 

        for(int d=0;d<dimension;d++)
        {
            w[d] = boost::json::value_to<double>(arr_weights->at(d)); 
        }
    }
    else
    {
        for(int d=0;d<dimension;d++)
        {
            this->w[d] = rand()%50 - 25;
        }   
    }
}

std::vector<double> EnvironmentLinear::generate_random_x()
{
    std::vector<double> random_x(dimension);

    for(int d=0; d<dimension;d++)
        random_x[d] = rand()%1000 - 500;

    return random_x;
}

double EnvironmentLinear::compute_linear(std::vector<double> x)
{
    // compute the linear transformation w1*x1 + ... + wn*xn + b
    double res = 0;
    for(int i=0; i<dimension;i++)
    {
        res += w[i] * x[i];
    }
    res += b;

    return res;
}

void EnvironmentLinear::evolve()
{
    this->init_values();
}

void EnvironmentLinear::init_values()
{
    for(int i=0; i<size_test+size_validation; i++)
    {
        std::vector<double> x = generate_random_x();
        double f_x = compute_linear(x);

        if(i<size_test)
        {
            env_values[i] = (QuantumDataAbstract) TestData(x, f_x);
        }
        else
        {
            env_values[i] = (QuantumDataAbstract) ValidationData(x, f_x);
        }
    }
}

//---------- other

std::string EnvironmentLinear::to_string()
{
    std::string res = Environment::to_string();

    res     +=      " dimension : " +std::to_string(dimension) + " weights : ";
    for(int i =0; i<dimension;i++) {
        res +=      std::to_string(w[i]) + " "; }
    res     +=      "bias : " + std::to_string(b);

    return res;
}

boost::json::object EnvironmentLinear::object_to_json()
{
    boost::json::object jenv = Environment::object_to_json();

    jenv["dimension"]   =   dimension;

    boost::json::array arr_weights;
    for(int i=0;i<dimension;i++) {
        arr_weights.emplace_back(w[i]); }
    jenv["weights"]     =   arr_weights;

    jenv["bias"]        =   b;

    return jenv;
}
