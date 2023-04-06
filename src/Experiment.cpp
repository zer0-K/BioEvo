#include <iostream>

#include "Experiment.hpp"
#include "Constants.hpp"

Experiment::Experiment()
    : Experiment(DEFAULT_UNIVERSE_WIDTH, DEFAULT_UNIVERSE_HEIGHT)
{

}

Experiment::Experiment(const int width, const int height)
{
    // does nothing
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