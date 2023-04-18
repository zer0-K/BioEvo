#pragma once

#include "../../../Individual.hpp"
#include "../../../Biology/Trait.hpp"

class LinearRegressionIndividual : Individual
{
private:
    int dimension;  ///< dimension 
    Trait<double>** w;  ///< coefficients of the linear model
    Trait<double>* b;   ///< affine term

    public:
    /**
     * @brief Constructor
     * @see Individual constructor
     * 
     * @param[in] dimension dimension of the model
    */
    LinearRegressionIndividual(std::string name, int dimension);

    /**
     * @brief Constructor
     * @see Individual constructor
     * 
     * @param[in] dimension dimension of the model
    */
    LinearRegressionIndividual(std::string name, int nb_epoch_learn, int dimension);

    /// @see Individual::evolve
    void evolve() override;

    /// @see Individual::compute
    Flow* compute(Flow* x) override;

    /**
     * @brief compute f_x for a given x
     * 
     * @param[in] x x (mathematical vector)
     * 
     * @return f(x)
    */
    double compute(double x[]);

    //-----other
    std::string to_string() override;
};