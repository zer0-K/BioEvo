#include "EnvironmentLinear.hpp"

#include <cstdlib>
#include <vector>
#include <iostream>

#include "../../PreprocessingDefinitions.hpp"
#include "../../Constants.hpp"
#include "../../Utils/Log/Logger.hpp"
#include "../../Utils/Convert/tostring.hpp"
#include "Flow/InputLinearEnvironment.hpp"
#include "Flow/OutputLinearEnvironment.hpp"

EnvironmentLinear::EnvironmentLinear(std::string name, int dimension, double w[], double b)
    :Environment::Environment(name)
{
    logger_write(2, FLAG_INIT + "Creating linear model environment...");

    this->dimension = dimension;
    this->w = w;
    this->b = b;

    this->input = (Flow*) new InputLinearEnvironment();

    logger_write(2,FLAG_INIT + name + " created. Linear model dimension : " + std::to_string(dimension) \
        + ", weights : " + convert_str(w, dimension) +", biases : " + std::to_string(b));
}

Pair<double,double>** EnvironmentLinear::generate_random_output(int individual_index, int nb_vals)
{
    auto generated_vals = new Pair<double,double>*[nb_vals];

    // generate values 
    for(int epoch=0; epoch<nb_vals; epoch++)
    {
        // create a random feature
        double* random_x = new double[this->dimension];
        for(int d=0; d<this->dimension;d++)
        {
            random_x[d] = rand()%1000 - 500;
        }

        // compute its image
        double f_random_x = this->compute_linear(random_x);
          
        // value for the current epoch (for current individual)
        generated_vals[epoch] = new Pair<double,double>(random_x, f_random_x);
    }

    return generated_vals;
}

void EnvironmentLinear::generate_random_ouputs(int nb_individuals, int nb_epochs_learn[])
{
    logger_write(2, FLAG_INFO + FLAG_EVOLVE + "Creating output of " + this->name);


    // generate input for each individual
    Pair<double,double>** output_vals[nb_individuals]; 
    for(int i=0; i<nb_individuals; i++)
    {
        // adds the generated ouput for the current individual
        output_vals[i] = this->generate_random_output(i, nb_epochs_learn[i]);
    }
    this->output = (Flow*) new OutputLinearEnvironment(output_vals, nb_epochs_learn);


    logger_write(2, FLAG_INFO + FLAG_EVOLVE + "Output of " + this->name + " created");
    logger_write(3, FLAG_INFO + FLAG_EVOLVE + FLAG_DETAILS + convert_str(output_vals[0], nb_epochs_learn[0], this->dimension));
}

double EnvironmentLinear::compute_linear(double x[])
{
    // compute the linear transformation w1*x1 + ... + wn*xn + b
    double res = 0;
    for(int i=0; i<this->dimension;i++)
    {
        res += w[i] * x[i];
    }
    res += b;

    return res;
}

void EnvironmentLinear::evolve(int nb_individuals, int nb_epochs[])
{
    logger_write(1, FLAG_INFO + FLAG_EVOLVE + FLAG_BEGIN + "Evolving + " + this->name);

    this->generate_random_ouputs(nb_individuals, nb_epochs);

    logger_write(1, FLAG_INFO + FLAG_EVOLVE + FLAG_END + this->name + " evolved");
}

void EnvironmentLinear::init(int nb_individuals, int nb_epochs[])
{
    logger_write(1, FLAG_INIT + FLAG_BEGIN + "Initializing " + this->name);

    this->generate_random_ouputs(nb_individuals, nb_epochs);

    logger_write(1, FLAG_INIT + FLAG_END + this->name + " initialized");
}

void EnvironmentLinear::compute(int nb_individuals, int nb_vals)
{
    logger_write(1, FLAG_INIT + FLAG_BEGIN + this->name + " computing " + std::to_string(nb_vals) + " values...");

    Pair<double,double>*** outputs = new Pair<double,double>**[nb_individuals];
    for(int i=0; i<nb_individuals;i++)
    {
        outputs[i] = this->generate_random_output(i, nb_vals);
    }

    // set output
    int* nb_vals_array = new int[nb_individuals];
    for(int i=0;i<nb_individuals;i++)
    {
        nb_vals_array[i] = nb_vals;
    }
    this->output = (Flow*) new OutputLinearEnvironment(outputs, nb_vals_array);

    logger_write(1, FLAG_INIT + FLAG_END + this->name + " has computed values");
}

//---------- other

std::string EnvironmentLinear::to_string()
{
    std::string res = Environment::to_string();

    res += " dimension : " +std::to_string(this->dimension) + " weights : ";
    for(int i =0; i<this->dimension;i++)
    {
        res += std::to_string(this->w[i]) + " ";
    }
    res += "bias : " + std::to_string(this->b);

    return res;
}

boost::json::object EnvironmentLinear::to_json()
{
    boost::json::object jenv = Environment::to_json();

    jenv["dimension"] = this->dimension;
    boost::json::array arr_weights;
    for(int i=0;i<this->dimension;i++)
        arr_weights.emplace_back(this->w[i]);
    jenv["weights"] = arr_weights;
    jenv["bias"] = this->b;

    /*
    std::string res = Environment::to_json();
    res.replace(res.size()-1,1,"");

    res += ",'dimension':" +std::to_string(this->dimension) + ",'weights':[";
    for(int i =0; i<this->dimension;i++)
    {
        res += std::to_string(this->w[i]) + ",";
    }
    res.replace(res.size()-1,1,"");
    res += "],'bias':" + std::to_string(this->b);
    res += "}";

    return res;*/
    return jenv;
}