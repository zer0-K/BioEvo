#include "EatingProcessor.hpp"

#include <iostream>

EatingProcessor::EatingProcessor(const int width, const int height)
    : EatingProcessor(width, height, DEFAULT_STARTING_ROW, DEFAULT_STARTING_COL)
{

}

EatingProcessor::EatingProcessor(const int width, const int height, int starting_row, int starting_col)
{
    //---------- spatial attributes
    this->width = width;
    this->height = height;
    this->starting_row = starting_row;
    this->starting_col = starting_col;

    //---------- computing attributes
    this->neighborhood_manager = new NeighborhoodManager(width, height);
    this->state_changer = new StateChanger(this->neighborhood_manager);

    //---------- other
    this->neighborhood_type = DEFAULT_NEIGHBORHOOD_TYPE;
}

void EatingProcessor::proceed(CodeEater*** code_eaters)
{
    // first read from the starting position to the end...
    for(int r=this->starting_row; r<this->height; r++)
    {
        for(int c=this->starting_col; c<this->width; c++)
        {
            this->apply(code_eaters, r, c);
        }
    }

    // then read from the begginning to the starting position
    for(int r=0; r<=this->starting_row; r++)
    {
        for(int c=0; c<this->starting_col; c++)
        {
            this->apply(code_eaters, r, c);
        }
    }
}

void EatingProcessor::apply(CodeEater*** code_eaters, int r, int c)
{
    // change the state of the current code eater and proceed the result (eat, spit)
     
    // get the code eater on which we apply the computing process
    CodeEater* code_eater = code_eaters[r][c];

    // get its neighborhood before proceeding to the eating/spittinh
    CodeEater** neighborhood = this->neighborhood_manager->getNeighborhood(code_eaters, r, c, this->neighborhood_type);

    // change the state of the code eater and proceed the result
    int neighbor_replacement_index = this->state_changer->changeState(code_eater, neighborhood, VON_NEUMANN);

    if(r==2 && c==3)
    {
        std::cout<<"a"<<std::endl;
    }
    
    // if the state change implies a neighbor to be replaced
    if(neighbor_replacement_index != -1)
    {
        // get the coordinates of the replacement
        int r_replacement;
        int c_replacement;
        this->neighborhood_manager->getAbsoluteReplacementCoordinates(r, c, neighbor_replacement_index, 
            this->neighborhood_type, r_replacement, c_replacement);


        // replace a code eater at the given coordinates !
        this->replace(code_eaters, r_replacement, c_replacement);
    }
}


void EatingProcessor::replace(CodeEater*** code_eaters, int r, int c)
{
    // if there is already a code eater, this is not expected
    if(code_eaters[r][c]->getToken() != EATER_TOKEN_EMPTY)
    {
#if DEBUG
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<"-------------------- ERROR ! -------------------- (beginning)"<<std::endl;
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<"In the eating processor, while replacing a code eater (method 'replace(...)'). ";
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<"There is already a code eater at ("<<r<<";"<<c<<"). Can't replace a code eater there..."<<std::endl;
        std::cout<<"The code eater "<<std::endl;
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<"-------------------- ERROR ! -------------------- (end)"<<std::endl;
        std::cout<<std::endl;
        std::cout<<std::endl;
#endif
    }
    // otherwise, replace a code eater
    else
    {
        // for the moment, replace a default code eater
        code_eaters[r][c] = new CodeEater();
    }
}