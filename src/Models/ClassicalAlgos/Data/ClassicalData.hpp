#pragma once

#include "../../../Entities/Entity.hpp"

class ClassicalData : public Entity
{
protected:
    std::vector<double> x;
    double f_x;

public:
    ClassicalData(std::vector<double> x, double f_x);
    ClassicalData(std::string name, std::vector<double> x, double f_x);

   void init() override;
    std::vector<sp_entity> exec(std::vector<sp_entity> entries) override;

    std::vector<double> get_x();
};

typedef std::shared_ptr<ClassicalData> sp_classical_data;