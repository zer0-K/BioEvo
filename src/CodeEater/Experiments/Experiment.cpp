#include <iostream>

#include "Experiment.hpp"
#include "../Constants.hpp"

Experiment::Experiment()
    : Experiment(DEFAULT_WIDTH, DEFAULT_HEIGHT)
{

}

Experiment::Experiment(const int width, const int height)
{
    this->code_eaters = new CodeEater**[height];

    // create the eating process
    this->eating_processor = new EatingProcessor(width, height);

    // create the universe
    this->universe = new Universe(this->eating_processor, this->code_eaters, width, height);

    // init the code eaters
    // actually useless here, you need to call it in the child constructor (Experiment1, Experiment2,...)
    this->initCodeEaters();
}

void Experiment::loop()
{
    int timestep = 1;
    
    while(timestep > 0)
    {
        std::cout<<"Enter a number of time steps (0 to stop): "<<std::endl;
        std::cin>>timestep;

        // proceed 'timestep' eating processes
        this->universe->nextSteps(timestep);
        // you can also perform a loop and call nextStep() to have more control
    }
}