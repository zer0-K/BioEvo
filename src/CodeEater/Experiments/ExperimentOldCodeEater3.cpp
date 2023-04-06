#include <iostream>

#include "ExperimentOldCodeEater3.hpp"

ExperimentOldCodeEater3::ExperimentOldCodeEater3()
    :ExperimentOldCodeEater()
{
    // after the parent constructor init, do some other stuff
    this->initExperimentOld();
}

void ExperimentOldCodeEater3::initExperimentOld()
{
    // place a code eater somewhere
    int r,c;r=DEFAULT_HEIGHT/2;c=DEFAULT_WIDTH/2;    
    
    delete this->code_eaters[r][c];     
    this->code_eaters[r][c] = new CodeEater(EATER_TOKEN_1, 72);
}

void ExperimentOldCodeEater3::launch()
{
    std::cout<<"***********************************"<<std::endl;
    std::cout<<"Launching ExperimentOldCodeEater 3"<<std::endl;
    std::cout<<"***********************************"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"ExperimentOldCodeEater 3 : introducing eating process"<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

    this->loop();
}