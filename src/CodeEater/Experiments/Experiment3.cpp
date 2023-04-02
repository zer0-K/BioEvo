#include <iostream>

#include "Experiment3.hpp"

Experiment3::Experiment3()
    :Experiment()
{
    // after the parent constructor init, do some other stuff
    this->initCodeEaters();
}

void Experiment3::initCodeEaters()
{
    // place a code eater somewhere
    int r,c;r=DEFAULT_HEIGHT/2;c=DEFAULT_WIDTH/2;    
    
    delete this->code_eaters[r][c];     
    this->code_eaters[r][c] = new CodeEater(EATER_TOKEN_1, 72);
}

void Experiment3::launch()
{
    std::cout<<"***********************************"<<std::endl;
    std::cout<<"Launching experiment 3"<<std::endl;
    std::cout<<"***********************************"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Experiment 3 : introducing eating process"<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

    this->loop();
}