#include "Constants.hpp"

//-------------------- Framework constants

const int DEFAULT_UNIVERSE_WIDTH        = 6;
const int DEFAULT_UNIVERSE_HEIGHT       = 6;
const int DEFAULT_NB_MAX_SOLUTIONS      = 3;
const int DEFAULT_NB_MAX_INDIVIDUALS    = 10;

//-------------------- Experiment numbers

const std::string EXPERIMENT_WEB                = "web interface";
const int EXPERIMENT_NUMBER_WEB                 = 0;

const std::string EXPERIMENT_CONFIG             = "choose config";
const int EXPERIMENT_NUMBER_CONFIG              = 1;

const std::string EXPERIMENT_CLASSICAL_ALGO_1   = "experiment classical algos 1";
const int EXPERIMENT_NUMBER_CLASSICAL_ALGOS     = 2;

const int EXPERIMENT_NUMBER_SELF_CHANGING_CODE  = 3;
const int EXPERIMENT_NUMBER_CODE_EATER          = 4;

const int DEFAULT_NB_EPOCHS_LEARN               = 100;
const int DEFAULT_NB_EPOCHS_EVO                 = 100;


//-------------------- Info on contents

std::vector<std::string> ENVIRONMENT_TYPES = std::vector<std::string> {
    "linear"
};
std::vector<std::string> INDIVIDUAL_TYPES = std::vector<std::string> {
    "linear"
};

//-------------------- Linear


//----- environment

const std::string ENV_NAME_LINEAR   = "environment linear models";
const int ENV_LINEAR_DEFAULT_DIMENSION = 4;
const double ENV_LINEAR_DEFAULT_BIAS = 0;

//----- individuals

const std::string INDIVIDUAL_NAME_LINEAR_LEARN  = "individual linear model learn";
const std::string INDIVIDUAL_NAME_LINEAR_SELECT = "individual linear model select";
const int INDIV_LINEAR_DEFAULT_DIMENSION = 4;
const double INDIV_LINEAR_DEFAULT_BIAS = 0;


//---------- universe names

const std::string UNIVERSE_NAME_CLASSICAL   = "universe classical algos";

//-------------------- All info on contents


std::vector<std::string> UNIVERSE_NAMES = std::vector<std::string>( {
    UNIVERSE_NAME_CLASSICAL
});

std::map<const std::string, std::vector<std::string>> ENV_NAMES_BY_UNIVERSE = {
    { 
        UNIVERSE_NAME_CLASSICAL,
        std::vector<std::string>({
            ENV_NAME_LINEAR
        }) 
    }
};

std::map<const std::string, std::vector<std::string>> INDIVIDUAL_NAMES_BY_ENV = {
    {
        ENV_NAME_LINEAR,
        std::vector<std::string>({
            INDIVIDUAL_NAME_LINEAR_LEARN,
            INDIVIDUAL_NAME_LINEAR_SELECT
        })
    }
};


//-------------------- types

std::string TYPE_INT    = "int";
std::string TYPE_STRING = "string";
std::string TYPE_DOUBLE = "double";
std::string TYPE_LIST   = "list";


//-------------------- Log flags

const std::string FLAG_INIT  = "[INIT] ";
const std::string FLAG_INFO  = "[INFO] ";
const std::string FLAG_ERROR = "[ERROR] ";
const std::string FLAG_WARN  = "[WARN] ";
const std::string FLAG_FRAMEWORK = "[FRAMEWORK] ";
const std::string FLAG_EVOLVE = "[EVOLVE] ";
const std::string FLAG_DETAILS = "[DETAIL] ";
const std::string FLAG_BEGIN = "[BEGIN] ";
const std::string FLAG_END = "[END] ";
const std::string FLAG_RESULT = "[RESULT] ";