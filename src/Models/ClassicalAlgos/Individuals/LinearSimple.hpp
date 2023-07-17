#pragma once

#include <vector>

#include "ClassicalIndividual.hpp"
#include "../Data/ClassicalData.hpp"

class LinearSimple : public ClassicalIndividual
{
public:
    LinearSimple(std::string name, int dim);
    LinearSimple(std::string name, std::vector<double> coeffs);
    LinearSimple(std::string name, std::vector<double> coeffs,
        std::vector<double> means, std::vector<double> std_devs);

    void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;

    void compute_single(sp_classical_data data);
};
