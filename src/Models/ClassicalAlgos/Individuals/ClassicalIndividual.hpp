#pragma once

#include <vector>

#include "../../../Entities/Entity.hpp"
#include "../Biology/Trait.hpp"
#include "../Biology/Gene/Gene.hpp"

class ClassicalIndividual : public Entity
{
protected:
    /**
     * @brief coefficients of the model
     * 
     * For a linear models, the coefficients of the model
     * For a neural network, can be the weigths or even the layer size
    */
    std::vector<sp_abstracttrait> coeffs;
    
    std::vector<sp_gene> phenotypic_body;

public:
    using Entity::Entity;

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;

    void update_coeffs();
};

typedef std::shared_ptr<ClassicalIndividual> sp_ca;