#include "IndividualLinear.hpp"

#include "../Biology/QuantumData/TestData.hpp"
#include "../Biology/QuantumData/ValidationData.hpp"
#include "../Declaration/Constants.hpp"
#include "../Utils/Math/RandomGen.hpp"
#include "../Utils/Log/Logger.hpp"
#include <random> 
#include <iostream>
#include <math.h>

IndividualLinear::IndividualLinear(std::string name, int dimension)
    :Individual::Individual(name)
{
    init();

    this->dimension = dimension;
    w = std::vector<std::shared_ptr<Trait<double>>>(dimension);

    for(int d=0;d<dimension;d++)
    {
        w[d] = std::make_shared<Trait<double>>(rand()%50 - 25);
        sp_abstracttrait weight_trait = w[d];
        weight_trait->set_name("weight " + std::to_string(d));
    }

    b = std::make_shared<Trait<double>>(0);
    sp_abstracttrait bias_trait = b;
    bias_trait->set_name("bias");
}

IndividualLinear::IndividualLinear(boost::json::object params)
    :Individual::Individual(params)
{
    this->init();

    boost::json::value* jdim = params.if_contains("dimension");
    boost::json::value* jweights = params.if_contains("weights");
    boost::json::value* jbias = params.if_contains("bias");

    // dimension
    if(jdim != nullptr)
        dimension = boost::json::value_to<int>(*jdim);
    else
        dimension = INDIV_LINEAR_DEFAULT_DIMENSION;

    // bias
    double bias;
    if(jbias != nullptr)
        bias = boost::json::value_to<double>(*jbias); 
    else
        bias = INDIV_LINEAR_DEFAULT_BIAS;
    b = std::make_shared<Trait<double>>(bias);
    sp_abstracttrait bias_trait = b;
    bias_trait->set_name("bias");

    // weights
    w = std::vector<std::shared_ptr<Trait<double>>>(dimension);
    if(jweights != nullptr && jweights->if_array() != nullptr)
    {
        boost::json::array* arr_weights = jweights->if_array(); 

        for(int d=0;d<dimension;d++)
        {
            w[d] = std::make_shared<Trait<double>>(
                boost::json::value_to<double>(arr_weights->at(d))
            );
            sp_abstracttrait weight_trait = w[d];
            weight_trait->set_name("weight " + std::to_string(d)); 
        }
    }
    else
    {
        for(int d=0;d<dimension;d++)
        {
            w[d] = std::make_shared<Trait<double>>(rand()%50 - 25);
            sp_abstracttrait weight_trait = w[d];
            weight_trait->set_name("weight " + std::to_string(d));
        }   
    }
}

void IndividualLinear::init()
{
    learning_method = 1;
    prec_change = 0;
    prec_diff = 0;
    prec_index = -1;
}

void IndividualLinear::evolve()
{
}

QuantumDataAbstract IndividualLinear::compute(QuantumDataAbstract x)
{
    /*
    sp_input_linear_individual x_as_linear = std::dynamic_pointer_cast<InputLinearIndividual>(
        x
    );
    Pair<double,double>** vals_pairs = x_as_linear->get_values();
    int nb_vals = x_as_linear->get_nb_vals();

    Pair<double,double>** new_vals = new Pair<double,double>*[nb_vals];
    for(int i=0;i<nb_vals;i++)
    {
        std::vector<double> x = vals_pairs[i]->get_x();

        double f_x = this->compute_single(x);
        switch (this->learning_method)
        {
        case 1:
            update_params_1(x, f_x, vals_pairs[i]->get_f_x());
            break;
        
        default:
            break;
        }

        new_vals[i] = new Pair<double, double>(x, f_x);
    }

    return std::make_shared<OutputLinearIndividual>(new_vals, nb_vals);
    */
    std::vector<double> temp(1);
    temp[0] =2;
    return (QuantumDataAbstract) TestData(temp,3);
}

void IndividualLinear::update_params_1(std::vector<double> x, double f_x, double f_x_true)
{
    // 
    // Here the algo learns with a certain random die-and-retry
    // It makes random changes and keeps only the ones that improve prediction
    // 

    if(prec_index > -1)
    {
        double diff = std::abs(f_x-f_x_true);
        double relative_diff = f_x!=0 ? diff/f_x : diff;

        // cancel change if the prediction is worse
        if(relative_diff>prec_diff)
        {
            double prec = w[prec_index]->get_value();
            w[prec_index]->set_value(prec-prec_change);
        }
    }

    int rand_index = std::rand()%dimension;
    prec_index = rand_index;
    
    // generate anew random change
    double val_to_change = w[rand_index]->get_value();
    double change = rand_gen::rand_normal(val_to_change,std::sqrt(std::abs(val_to_change))/24);
    prec_change = change;
    w[rand_index]->set_value(val_to_change+change);

    prec_diff = f_x_true==0 ? std::abs(f_x) : std::abs(f_x-f_x_true)/f_x_true;

    logger_write(1, FLAG_INFO + FLAG_DETAILS + "Params updated : " + this->to_string());
}

double IndividualLinear::compute_single(std::vector<double> x)
{
    // compute the linear transformation w1*x1 + ... + wn*xn + b
    double res = 0;
    for(int i=0; i<dimension;i++)
    {
        res += w[i]->get_value() * x[i];
    }
    res += b->get_value();

    return res;
}

//---------- other

std::string IndividualLinear::to_string()
{
    std::string res = Individual::to_string();

    res += name + " :  weights : ";
    for(int i=0;i<dimension;i++)
    {
        res += std::to_string(w[i]->get_value()) + " ";
    }
    res += ", bias : " + std::to_string(b->get_value());
    res += ", prec error (relative): " + std::to_string(prec_diff);

    return res;
}

boost::json::object IndividualLinear::object_to_json()
{
    boost::json::object jindividual = Individual::object_to_json();

    jindividual["dimension"] = dimension;

    boost::json::array arr_weights;
    for(int i=0;i<dimension;i++)
        arr_weights.emplace_back(w[i]->get_value());
    jindividual["weights"] = arr_weights;

    jindividual["bias"] = b->get_value();
    jindividual["error"] = prec_diff;

    return jindividual;
}

