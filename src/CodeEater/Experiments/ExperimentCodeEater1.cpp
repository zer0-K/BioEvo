#include <iostream>

#include "ExperimentCodeEater1.hpp"

ExperimentCodeEater1::ExperimentCodeEater1():ExperimentCodeEater()
{
    // after the parent constructor init, do some other stuff
    this->initExperiment();
}

void ExperimentCodeEater1::initExperiment()
{
    // do nothing for ExperimentCodeEater 1
}

void ExperimentCodeEater1::launch()
{
    std::cout<<"***********************************"<<std::endl;
    std::cout<<"Launching ExperimentCodeEater 1"<<std::endl;
    std::cout<<"***********************************"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"ExperimentCodeEater 1 : empty code eaters, to test that the simulator is working"<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

    this->show();
}