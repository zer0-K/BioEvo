#include "Constants.hpp"

//---------- Framework constants

const int DEFAULT_UNIVERSE_WIDTH = 6;
const int DEFAULT_UNIVERSE_HEIGHT = 6;
const int DEFAULT_NB_MAX_SOLUTIONS = 3;
const int DEFAULT_NB_MAX_INDIVIDUALS = 10;

//---------- Experiment numbers

const std::string EXPERIMENT_CLASSICAL_ALGO_1 = "experiment classical algos 1";
const int EXPERIMENT_NUMBER_CLASSICAL_ALGOS = 0;

const int EXPERIMENT_NUMBER_SELF_CHANGING_CODE = 1;
const int EXPERIMENT_NUMBER_CODE_EATER = 2;

const int DEFAULT_NB_EPOCHS_LEARN = 100;
const int DEFAULT_NB_EPOCHS_EVO = 100;

//---------- Log flags

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