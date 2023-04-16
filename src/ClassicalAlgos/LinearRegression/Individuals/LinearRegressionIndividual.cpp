#include "LinearRegressionIndividual.hpp"

#include "../Flow/InputLinearIndividual.hpp"
#include "../Flow/OutputLinearIndividual.hpp"
#include "../../../Constants.hpp"
#include <random> 

LinearRegressionIndividual::LinearRegressionIndividual(std::string name, int dimension)
    :LinearRegressionIndividual::LinearRegressionIndividual(name, DEFAULT_NB_EPOCHS_LEARN, dimension)
{
    // do nothing here
}

LinearRegressionIndividual::LinearRegressionIndividual(std::string name, int nb_epoch_learn, int dimension)
    :Individual::Individual(name, nb_epoch_learn)
{
    this->dimension = dimension;
    this->w = new double[dimension];

    for(int d=0;d<dimension;d++)
    {
        this->w[d] = rand()%100 - 50;
    }
    this->b = rand()%100 - 50;

    this->output = (Flow*) new OutputLinearIndividual(NULL, 0);
}

void LinearRegressionIndividual::evolve()
{
    double grad = 1000;
    double learning_rate = 0.5f;

    int epoch=0;
    while(epoch<=this->number_of_epochs || grad<0.001f)
    {
        epoch++; 
    }
}

Flow* LinearRegressionIndividual::compute(Flow* x)
{
    InputLinearIndividual* x_as_linear = (InputLinearIndividual*) x;
    Pair<double,double>** vals_pairs = x_as_linear->get_values();
    int nb_vals = x_as_linear->get_nb_vals();

    Pair<double,double>** new_vals = new Pair<double,double>*[nb_vals];
    for(int i=0;i<nb_vals;i++)
    {
        double* x = vals_pairs[i]->get_x();
        double f_x = this->compute(x);
        new_vals[i] = new Pair<double, double>(x, f_x);
    }

    OutputLinearIndividual* individual_output = new OutputLinearIndividual(new_vals, nb_vals);

    return (Flow*) individual_output;
}

double LinearRegressionIndividual::compute(double x[])
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