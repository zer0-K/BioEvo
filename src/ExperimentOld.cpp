#include <iostream>

#include "ExperimentOld.hpp"
#include "Declaration/Constants.hpp"

ExperimentOld::ExperimentOld()
    : ExperimentOld(DEFAULT_UNIVERSE_WIDTH, DEFAULT_UNIVERSE_HEIGHT)
{

}

ExperimentOld::ExperimentOld(const int width, const int height)
{
    // does nothing
}

void ExperimentOld::loop()
{
    int timestep = 1;
    
    while(timestep > 0)
    {
        std::cout<<"Enter a number of time steps (0 to stop): "<<std::endl;
        std::cin>>timestep;

        // proceed 'timestep' eating processes
        this->universe->next_step();
        // you can also perform a loop and call next_step() to have more control
    }
}