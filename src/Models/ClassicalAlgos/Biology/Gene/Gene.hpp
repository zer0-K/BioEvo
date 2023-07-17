#pragma once

#include "../Trait.hpp"

/// @brief Gene
class Gene
{
protected:
    sp_abstracttrait trait_driven;  ///< Trait that the gene drives

public:
    /**
     * @brief Constructor
     * 
    * @param[in] trait trait that the gene drives
    */
    Gene(sp_abstracttrait trait);

    /**
     * @brief Tell how the gene drives the trait
    */
    virtual void drive() = 0;

    //----- getters
    sp_abstracttrait get_trait();
};

typedef std::shared_ptr<Gene> sp_gene;