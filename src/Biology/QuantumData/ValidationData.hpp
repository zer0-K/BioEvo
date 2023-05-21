#pragma once

#include <vector>

#include "QuantumData.hpp"

class ValidationData : public QuantumData<std::vector<double>, double>
{
public:
    /**
     * @brief @see QuantumData constructor
    */
    ValidationData(std::vector<double> x, double f_x);
};

typedef std::shared_ptr<ValidationData> sp_validationdata;