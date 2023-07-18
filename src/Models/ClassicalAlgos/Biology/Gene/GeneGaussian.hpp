#pragma once

#include "Gene.hpp"

/// @brief Simple gaussian gene
class GeneGaussian : public Gene
{
protected:
    Trait<double> mean;        ///< mean of the values generated by the gene
    Trait<double> std_dev;     ///< std dev of the values generated by the gene

public:
    /**
     * @brief Constructor
     * 
     * @param[in] mean_val mean
     * @param[in] std_dev_val standard deviation 
     * @param[in] trait trait that the gene drives
    */
    GeneGaussian(double mean_val, double std_dev_val, std::shared_ptr<Trait<double>> trait);

    /**
     * @brief Drives with a simple gaussian generation
    */
    void drive() override;

    //----- setters
    void set_mean(double m);
    void set_std_dev(double s);
};

typedef std::shared_ptr<GeneGaussian> sp_gene_gauss;