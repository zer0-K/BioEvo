#pragma once

#include "Individual.hpp"
#include "../Biology/Trait.hpp"

class IndividualLinear : public Individual
{
private:
    int dimension;  ///< dimension 
    std::vector<std::shared_ptr<Trait<double>>> w;  ///< coefficients of the linear model
    std::shared_ptr<Trait<double>> b;   ///< affine term

    // ad hoc params
    int learning_method;    ///< learning method
    double prec_diff;
    int prec_index;
    double prec_change;

    public:
    /**
     * @brief Constructor
     * @see Individual constructor
     * 
     * @param[in] dimension dimension of the model
    */
    IndividualLinear(std::string name, int dimension);

    /**
     * @brief Constructor
     * @see Individual constructor
     * 
     * @param[in] dimension dimension of the model
    */
    IndividualLinear(std::string name, int nb_epoch_learn, int dimension);

    /// @brief init
    void init();

    /// @see Individual::evolve
    void evolve() override;

    /// @see Individual::compute
    std::shared_ptr<Flow> compute(std::shared_ptr<Flow> x) override;

    // learning methods
    void update_params_1(std::vector<double> x, double f_x, double f_x_true);

    /**
     * @brief compute f_x for a given x
     * 
     * @param[in] x x (mathematical vector)
     * 
     * @return f(x)
    */
    double compute_single(std::vector<double> x);

    //-----other
    std::string to_string() override;
    boost::json::object to_json() override;
};

typedef std::shared_ptr<IndividualLinear> sp_individual_linear;