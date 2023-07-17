#include "ClassicalData.hpp"

#include "../../../Utils/Constants.hpp"

ClassicalData::ClassicalData(std::vector<double> x, double f_x)
    :ClassicalData::ClassicalData("classical data", x, f_x)
{

}

ClassicalData::ClassicalData(std::string name, std::vector<double> x, double f_x)
    :Entity::Entity(name)
{
    this->x = x;
    this->f_x = f_x;
}

void ClassicalData::init()
{
    //Entity::init();

    type = CA_DATA;
    add_type(CA_DATA);
}

std::vector<sp_entity> ClassicalData::exec(std::vector<sp_entity> entries)
{
    // does nothing

    return entries;
}

std::vector<double> ClassicalData::get_x()
{
    return x;
}