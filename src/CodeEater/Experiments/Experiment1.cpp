#include <iostream>

#include "Experiment1.hpp"

Experiment1::Experiment1():Experiment()
{

}

void Experiment1::initCodeEaters()
{
    // do nothing for experiment 1
}

void Experiment1::launch()
{
    std::cout<<"***********************************"<<std::endl;
    std::cout<<"Launching experiment 1"<<std::endl;
    std::cout<<"***********************************"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Experiment 1 : empty code eaters, to test that the simulator is working"<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    
    this->universe->show();
}