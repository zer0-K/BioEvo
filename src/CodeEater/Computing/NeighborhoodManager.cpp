#include "NeighborhoodManager.hpp"

#include <iostream>

NeighborhoodManager::NeighborhoodManager(int width, int height)
{
    this->width = width;
    this->height = height;
}

//-------------------- general methods

CodeEater** NeighborhoodManager::getNeighborhood(CodeEater*** code_eaters, int r, int c, NeighborHoodType neighborhood_type)
{
    switch (neighborhood_type)
    {
    case VON_NEUMANN:
        return this->getVonNeumannNeighborhood(code_eaters, r, c);
        break;
    
    default:
        // for the moment, the default neighborhood is the Von Neumann neighborhood
        return this->getVonNeumannNeighborhood(code_eaters, r, c);
        break;
    }
}

void NeighborhoodManager::getAbsoluteReplacementCoordinates(int r, int c, int index, NeighborHoodType neighborhood_type, 
    int& r_replacement, int& c_replacement)
{
    switch (neighborhood_type)
    {
    case VON_NEUMANN:
        return this->getAbsoluteReplacementCoordinates_VonNeumann(r, c, index, r_replacement, c_replacement);
        break;
    
    default:
        // for the moment, the default neighborhood is the Von Neumann neighborhood
        return this->getAbsoluteReplacementCoordinates_VonNeumann(r, c, index, r_replacement, c_replacement);
        break;
    }
}


int NeighborhoodManager::getNeighborIndexFromDirection(NeighborHoodType neighborhood_type, EatDirection direction)
{
    switch (neighborhood_type)
    {
    case RIGHT:
        if(direction == NO_DIRECTION)
            return -1;
        if(direction == RIGHT_DIRECTION)
            return 0;
        break;

    case LEFT:
        if(direction == NO_DIRECTION)
            return -1;
        if(direction == LEFT_DIRECTION)
            return 0;
        break;

    case LEFT_AND_RIGHT:
        if(direction == NO_DIRECTION)
            return -1;
        if(direction == LEFT_DIRECTION)
            return 0;
        if(direction == RIGHT_DIRECTION)
            return 1;
        break;

    case VON_NEUMANN:
        if(direction == NO_DIRECTION)
            return -1;
        if(direction == UP_DIRECTION)
            return 0;
        if(direction == RIGHT_DIRECTION)
            return 1;
        if(direction == DOWN_DIRECTION)
            return 2;
        if(direction == LEFT_DIRECTION)
            return 3;
        break;

    case NO_NEIGHBOR:    
    default:
        // when an eaten code eater has no neighbors for ex
        return -1;
        break;
    }
#if DEBUG
    // if invalid direction, return -1 (happens often, when an eaten code eater tries to eat up for ex)
    std::cout<<"Trying to get an invalid direction (happens often, when an eaten code eater tries to eat up for ex). ";
    std::cout<<"Delete this cout if it pollutes the terminal (in NeighorhoodManager::getNeighborIndexFromDirection). "<<std::endl;
#endif
    return -1;
}


//-------------------- more particular methods

//---------- Von Neumann

CodeEater** NeighborhoodManager::getVonNeumannNeighborhood(CodeEater*** code_eaters, int r, int c)
{
    CodeEater** neighbors_VonNeumann = new CodeEater*[4];

    // !!!! r-1 is considered as 'UP' because counting in computing starts at top left, so 
    // when going down on the screen the indexes are raising, and when going right too !!!!

    // modular stuff (with %) is because the space is a torus : above the first row (0) is the last one (height-1)

    // the first code eater is the up one
    neighbors_VonNeumann[INDEX_UP] = code_eaters[(r+this->height-1)%this->height][c];  // '+height-1' because (0-1)%height = -1...

    // the second code eater is the right one
    neighbors_VonNeumann[INDEX_RIGHT] = code_eaters[r][(c+1)%this->width];

    // the third code eater is the down one
    neighbors_VonNeumann[INDEX_DOWN] = code_eaters[(r+1)%this->height][c];

    // the last code eater is the left one
    neighbors_VonNeumann[INDEX_LEFT] = code_eaters[r][(c+this->width-1)%this->width];   // '+width-1' because (0-1)%width = -1...

    return neighbors_VonNeumann;
}

void NeighborhoodManager::getAbsoluteReplacementCoordinates_VonNeumann(int r, int c, int index, int& r_replacement, int& c_replacement)
{
    switch (index)
    {
    case INDEX_UP:
        r_replacement = (r+this->height-1)%this->height;  // '+height-1' because (0-1)%height = -1..
        c_replacement = c;
        break;

    case INDEX_RIGHT:
        r_replacement = r;
        c_replacement = (c+1)%this->width;
        break;

    case INDEX_DOWN:
        r_replacement = (r+1)%this->height;
        c_replacement = c;
        break;

    case INDEX_LEFT:
        r_replacement = r;
        c_replacement = (c+this->width-1)%this->width; // '+width-1' because (0-1)%width = -1...
        break;
    
    default:
#if DEBUG
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<"-------------------- ERROR ! -------------------- (beginning)"<<std::endl;
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<"In the neighborhood manager, while getting absolute replacement coordinates of a ";
        std::cout<<"code eater in a Von Neumann neighborhood ";
        std::cout<<"(method 'getAbsoluteReplacementCoordinates_VonNeumann(...)'). "<<std::endl;
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<"Neighborhood index invalid : Von Neumann neighborhood of the code eater at ";
        std::cout<<"("<<r<<";"<<c<<"). Von Neumann neighborhood has only 4 code eaters, given index : ";
        std::cout<<index<<" ; should be between 0 and 3. -1 is for 'no replacement', but this method shouldn't be ";
        std::cout<<"called if there is no replacement needed"<<std::endl;
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<"-------------------- ERROR ! -------------------- (end)"<<std::endl;
        std::cout<<std::endl;
        std::cout<<std::endl;
#endif
        break;
    }
}