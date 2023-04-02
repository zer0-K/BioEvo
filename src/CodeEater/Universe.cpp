#include <iostream>

#include "Universe.hpp"
#include "Constants.hpp"

Universe::Universe(EatingProcessor* eating_processor, CodeEater*** code_eaters, 
    const int width, const int height)
        : Universe(eating_processor, code_eaters, width, height, DEFAULT_STARTING_ROW, DEFAULT_STARTING_COL)
{
    // call the other constructor, that's all
}

Universe::Universe(EatingProcessor* eating_processor, CodeEater*** code_eaters, 
    const int width, const int height, int starting_width, int starting_height)
{
    // set eating process
    this->eating_processor = eating_processor;

    // init the scalars
    this->initScalars(width, height, starting_width, starting_height);

    // init code eaters
    this->initCodeEAters(code_eaters, width, height);

    // set initial universe state
    this->state = INITIAL_UNIVERSE_STATE;
}

Universe::~Universe()
{
    // does nothing, the code eaters need to be freed elsewhere !
}



//-------------------- init

void Universe::initScalars(const int width, const int height, int starting_row, int starting_col)
{
    // set time
    this->t = 0;

    // set spatial parameters
    this->width = width;
    this->height = height;
    this->starting_row = starting_row;
    this->starting_col = starting_col;
}


void Universe::initCodeEAters(CodeEater*** code_eaters, const int width, const int height)
{
    // set eaters, given by the Experiment
    this->code_eaters = code_eaters;

    // default code eaters completion
    for(int h=0; h<height; h++)
    {
        // new row of code eaters
        CodeEater** row_code_eaters = new CodeEater*[width];

        // complete the new row
        for(int w=0; w<width; w++)
        {
            row_code_eaters[w] = new CodeEater();
        }

        // add the new row
        this->code_eaters[h] = row_code_eaters;
    }
}



//-------------------- show

void Universe::show()
{
    for(int r=0; r<height; r++)
    {
        for(int c=0; c<height; c++)
        {
            this->code_eaters[r][c]->show();
        }
        std::cout<<std::endl;
    }

    std::cout<<std::endl<<std::endl<<std::endl;
}



//-------------------- next step

void Universe::nextStep()
{
    this->t++;

    // PROCEED THE EATING
    this->eating_processor->proceed(this->code_eaters);

    // DO NOT UPDATE HERE : the scalar update happens in 
    // the eating process (it gives some its values)
}


void Universe::nextSteps(int nb_steps)
{
    // check that the number of steps is valid
    if(nb_steps>0)
    {
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



//-------------------- getters

int Universe::getWidth()
{
    return this->width;
}

int Universe::getHeight()
{
    return this->height;
}

CodeEater*** Universe::getCodeEaters()
{
    return this->code_eaters;
}