#include <iostream>

#include "Universe.hpp"
#include "Constants.hpp"

Universe::Universe(const int width, const int height)
{
    this->width = width;
    this->height = height;
}

Universe::~Universe()
{
    // does nothing
}


void Universe::nextSteps(int nb_steps)
{
    // check that the number of steps is valid
    if(nb_steps>0)
    {

#if DEBUG
        std::cout<<"---------------- Looping "<<nb_steps<<" step(s) ----------------- (beginning) "<<std::endl;
#endif

        // perform the steps
        for(int i=0;i<nb_steps;i++)
        {
#if DEBUG
            std::cout<<"-------------------- step "<<i<<" -------------------- (beginning) "<<std::endl;
#endif
            this->nextStep();
#if DEBUG
            std::cout<<"-------------------- step "<<i<<" -------------------- (end) "<<std::endl;
#endif
        }

        // show
        this->show();
    }
    else if(nb_steps==0)
    {
        std::cout<<"Halting program. "<<std::endl;
    }
    else
    {
        std::cout<<"Wrong number of steps entered, should be > 0. "<<std::endl;
    }
}

void Universe::nextStep()
{
    // first, feed inputs with the outputs of the other
    // TODO more complex feeding ?
    for(int individual_i=0; individual_i<this->number_of_individuals; individual_i++)
    {
        this->buffer->feed_ins_and_outs(this->individuals[individual_i], this->environment);
    }

    // TODO allow the experimenter to act between each of the steps ?

    // then, makes the individuals and the environment evolve
    for(int individual_i=0; individual_i<this->number_of_individuals; individual_i++)
    {
        this->individuals[individual_i]->evolve();
    }
    this->environment->evolve();
}



//-------------------- getters

int Universe::getWidth()
{
    return this->width;
}

int Universe::getHeight()
{
    return this->height;
}