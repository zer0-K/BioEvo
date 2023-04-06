#include <iostream>

#include "ExperimentCodeEater3.hpp"

ExperimentCodeEater3::ExperimentCodeEater3()
    :ExperimentCodeEater()
{
    // after the parent constructor init, do some other stuff
    this->initExperiment();
}

void ExperimentCodeEater3::initExperiment()
{
    // place a code eater somewhere
    int r,c;r=DEFAULT_HEIGHT/2;c=DEFAULT_WIDTH/2;    
    
    delete this->code_eaters[r][c];     
    this->code_eaters[r][c] = new CodeEater(EATER_TOKEN_1, 72);
}

void ExperimentCodeEater3::launch()
{
    std::cout<<"***********************************"<<std::endl;
    std::cout<<"Launching ExperimentCodeEater 3"<<std::endl;
    std::cout<<"***********************************"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"ExperimentCodeEater 3 : introducing eating process"<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

    this->loop();
}