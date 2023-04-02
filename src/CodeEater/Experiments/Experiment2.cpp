#include <iostream>

#include "Experiment2.hpp"

Experiment2::Experiment2():Experiment()
{
}

void Experiment2::initCodeEaters()
{
    // place a code eater somewhere
    int h,w;h=4;w=4;    delete this->code_eaters[h][w];     this->code_eaters[h][w] = new CodeEater(EATER_TOKEN_1);
}


void Experiment2::launch()
{
    std::cout<<"***********************************"<<std::endl;
    std::cout<<"Launching experiment 2"<<std::endl;
    std::cout<<"***********************************"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Experiment 2 : introducing time, with one right eaters that still cannot eat"<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

    this->loop();
}