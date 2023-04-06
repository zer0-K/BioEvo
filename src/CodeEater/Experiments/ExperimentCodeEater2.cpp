#include <iostream>

#include "ExperimentCodeEater2.hpp"

ExperimentCodeEater2::ExperimentCodeEater2():ExperimentCodeEater()
{
    // after the parent constructor init, do some other stuff
    this->initExperiment();
}

void ExperimentCodeEater2::initExperiment()
{
    // place a code eater somewhere
    int h,w;h=4;w=4;    delete this->code_eaters[h][w];     this->code_eaters[h][w] = new CodeEater(EATER_TOKEN_1);
}


void ExperimentCodeEater2::launch()
{
    std::cout<<"***********************************"<<std::endl;
    std::cout<<"Launching ExperimentCodeEater 2"<<std::endl;
    std::cout<<"***********************************"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"ExperimentCodeEater 2 : introducing time, with one right eaters that still cannot eat"<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

    this->loop();
}