#pragma once

#include "AbstractTrait.hpp"

/// @brief Gene
class Gene
{
protected:
    double mean;    ///< mean of the values generated by the gene
    double std_dev;     ///< std dev of the values generated by the gene
    AbstractTrait* trait_driven;

public:
    /**
     * @brief Constructor
     * 
     * @param[in] mean mean
     * @param[in] std_dev standard deviation 
     * @param[in] trait trait that the gene drives
    */
    Gene(double mean, double std_dev, AbstractTrait* trait);

    /**
     * @brief Tell how the gene drives the trait
    */
    virtual void drive() = 0;

    //----- getters
    AbstractTrait* get_trait();

    //----- other
    std::string to_string();
    std::string to_json();
};