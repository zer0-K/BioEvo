#include <iostream>

#include "ExperimentOldCodeEater2.hpp"

ExperimentOldCodeEater2::ExperimentOldCodeEater2():ExperimentOldCodeEater()
{
    // after the parent constructor init, do some other stuff
    this->initExperimentOld();
}

void ExperimentOldCodeEater2::initExperimentOld()
{
    // place a code eater somewhere
    int h,w;h=4;w=4;    delete this->code_eaters[h][w];     this->code_eaters[h][w] = new CodeEater(EATER_TOKEN_1);
}


void ExperimentOldCodeEater2::launch()
{
    std::cout<<"***********************************"<<std::endl;
    std::cout<<"Launching ExperimentOldCodeEater 2"<<std::endl;
    std::cout<<"***********************************"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"ExperimentOldCodeEater 2 : introducing time, with one right eaters that still cannot eat"<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

    this->loop();
}