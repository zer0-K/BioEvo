#pragma once

enum EaterToken {
    EATER_TOKEN_TRIVIAL,
    EATER_TOKEN_1,
    EATER_TOKEN_EMPTY
};

enum NeighborHoodType
{
    NO_NEIGHBOR,
    VON_NEUMANN,
    MOORE,
    LEFT,
    RIGHT,
    LEFT_AND_RIGHT
};

enum Rule
{
    DO_NOTHING,
    EAT_RIGHT,
    EAT_LEFT,
    EAT_UP,
    EAT_DOWN,
    Count
};

enum EatDirection
{
    NO_DIRECTION,
    UP_DIRECTION,
    RIGHT_DIRECTION,
    DOWN_DIRECTION,
    LEFT_DIRECTION
};


//---------- universe size

const int DEFAULT_WIDTH = 6;   ///< universe default width
const int DEFAULT_HEIGHT = 6;  ///< universe default height


//---------- eating process parameters, related to the universe

const int DEFAULT_STARTING_ROW = 0; ///< default starting row of the eating process
const int DEFAULT_STARTING_COL = 0; ///< default starting column of the eating process
const int MAX_EATING_DEPTH = 3; ///< max number of layers
const int MAX_LAYER_SIZE = 5;   ///< max number of code eaters in a layer
const int INITIAL_UNIVERSE_STATE = true;    ///< initial universe state
const int MAX_NEIGHBORS = 4;



//---------- code eaters params

const int DEFAULT_IDENTIFIER = 0;   ///< default identifier for code eaters
const int DEFAULT_LIFETIME = 0;     ///< default lifetime for code eaters
const EaterToken DEFAULT_EATER_TYPE = EATER_TOKEN_TRIVIAL;    ///< default eater token
const int MAX_EATING_CODE_EATER = 5;    ///< max number of code eater a code eater can eat



//---------- computing params

const int NUMBER_OF_RULES = Rule::Count;  ///< default number of rules



//---------- Neighborhood constants

const NeighborHoodType DEFAULT_NEIGHBORHOOD_TYPE = VON_NEUMANN;

//----- Von Neumann

const int NUMBER_OF_NEIGHBORS_VON_NEUMANN = 4;
const int INDEX_UP = 0;
const int INDEX_RIGHT = 1;
const int INDEX_DOWN = 2;
const int INDEX_LEFT = 3;