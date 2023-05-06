#include "IndividualLinear.hpp"

#include "../Flow/InputLinearIndividual.hpp"
#include "../Flow/OutputLinearIndividual.hpp"
#include "../Declaration/Constants.hpp"
#include "../Utils/Math/RandomGen.hpp"
#include "../Utils/Log/Logger.hpp"
#include <random> 
#include <iostream>
#include <math.h>

IndividualLinear::IndividualLinear(std::string name, int dimension)
    :IndividualLinear::IndividualLinear(name, DEFAULT_NB_EPOCHS_LEARN, dimension)
{
    // do nothing here
}

IndividualLinear::IndividualLinear(std::string name, int nb_epoch_learn, int dimension)
    :Individual::Individual(name, nb_epoch_learn)
{
    this->init();

    this->dimension = dimension;
    this->w = std::vector<std::shared_ptr<Trait<double>>>(dimension);

    for(int d=0;d<dimension;d++)
    {
        this->w[d] = std::make_shared<Trait<double>>(rand()%50 - 25);
        sp_abstracttrait weight_trait = this->w[d];
        weight_trait->set_name("weight " + std::to_string(d));
    }

    this->b = std::make_shared<Trait<double>>(0);
    sp_abstracttrait bias_trait = this->b;
    bias_trait->set_name("bias");

    Pair<double,double>* input_vals[1];
    this->output = std::make_shared<OutputLinearIndividual>(input_vals, 0);
}

void IndividualLinear::init()
{
    this->learning_method = 1;
    this->prec_change = 0;
    this->prec_diff = 0;
    this->prec_index = -1;
}

void IndividualLinear::evolve()
{
    this->compute(this->input);     
}

sp_flow IndividualLinear::compute(sp_flow x)
{
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
}

void IndividualLinear::update_params_1(std::vector<double> x, double f_x, double f_x_true)
{
    // 
    // Here the algo learns with a certain random die-and-retry
    // It makes random changes and keeps only the ones that improve prediction
    // 

    if(this->prec_index > -1)
    {
        double diff = std::abs(f_x-f_x_true);
        double relative_diff = f_x!=0 ? diff/f_x : diff;

        // cancel change if the prediction is worse
        if(relative_diff>this->prec_diff)
        {
            double prec = this->w[this->prec_index]->get_value();
            this->w[this->prec_index]->set_value(prec-this->prec_change);
        }
    }

    int rand_index = std::rand()%this->dimension;
    this->prec_index = rand_index;
    
    // generate anew random change
    double val_to_change = this->w[rand_index]->get_value();
    double change = rand_gen::rand_normal(val_to_change,std::sqrt(std::abs(val_to_change))/24);
    this->prec_change = change;
    this->w[rand_index]->set_value(val_to_change+change);

    this->prec_diff = f_x_true==0 ? std::abs(f_x) : std::abs(f_x-f_x_true)/f_x_true;

    logger_write(1, FLAG_INFO + FLAG_DETAILS + "Params updated : " + this->to_string());
}

double IndividualLinear::compute_single(std::vector<double> x)
{
    // compute the linear transformation w1*x1 + ... + wn*xn + b
    double res = 0;
    for(int i=0; i<this->dimension;i++)
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

    res += this->name + " :  weights : ";
    for(int i=0;i<this->dimension;i++)
    {
        res += std::to_string(this->w[i]->get_value()) + " ";
    }
    res += ", bias : " + std::to_string(b->get_value());
    res += ", prec error (relative): " + std::to_string(this->prec_diff);

    return res;
}

boost::json::object IndividualLinear::to_json()
{
    boost::json::object jindividual = Individual::to_json();

    jindividual["dimension"] = this->dimension;
    boost::json::array arr_weights;
    for(int i=0;i<this->dimension;i++)
        arr_weights.emplace_back(this->w[i]->get_value());
    jindividual["weights"] = arr_weights;
    jindividual["bias"] = this->b->get_value();
    jindividual["error"] = this->prec_diff;

    /*
    std::string res = Individual::to_json();
    res.replace(res.size()-1,1,"");

    res += ",'dimension':" + std::to_string(this->dimension) + ",'weights':[";
    for(int i=0;i<this->dimension;i++)
    {
        res += std::to_string(this->w[i]->get_value()) + ",";
    }
    res += ",'bias':" + std::to_string(b->get_value());
    res += ",'prec error (relative)':" + std::to_string(this->prec_diff);

    return res;*/
    return jindividual;
}