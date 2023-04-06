#include <iostream>

#include "ExperimentOldCodeEater1.hpp"

ExperimentOldCodeEater1::ExperimentOldCodeEater1():ExperimentOldCodeEater()
{
    // after the parent constructor init, do some other stuff
    this->initExperimentOld();
}

void ExperimentOldCodeEater1::initExperimentOld()
{
    // do nothing for ExperimentOldCodeEater 1
}

void ExperimentOldCodeEater1::launch()
{
    std::cout<<"***********************************"<<std::endl;
    std::cout<<"Launching ExperimentOldCodeEater 1"<<std::endl;
    std::cout<<"***********************************"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"ExperimentOldCodeEater 1 : empty code eaters, to test that the simulator is working"<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

    this->show();
}