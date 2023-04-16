#include <string>

//---------- Framework constants

extern const int DEFAULT_UNIVERSE_WIDTH;    ///< Universe default width
extern const int DEFAULT_UNIVERSE_HEIGHT;   ///< Universe default height
extern const int DEFAULT_NB_MAX_SOLUTIONS;  ///< default number of maximum solutions we want to evolve
extern const int DEFAULT_NB_MAX_INDIVIDUALS;///< default number of maximum of individuals in the universe


//---------- Experiment

extern const std::string EXPERIMENT_CLASSICAL_ALGO_1;   ///< name of the first classical algo experiment
extern const int EXPERIMENT_NUMBER_CLASSICAL_ALGOS;     ///< number for classical algos

extern const int EXPERIMENT_NUMBER_SELF_CHANGING_CODE;  ///< number for self changing codes
extern const int EXPERIMENT_NUMBER_CODE_EATER;          ///< number for code eaters

extern const int DEFAULT_NB_EPOCHS_LEARN;       ///< default number of epoch for learning (1 individual lifetime)
extern const int DEFAULT_NB_EPOCHS_EVO;         ///< default number of epoch for evolution (several lifetimes)


//---------- Log flags

extern const std::string FLAG_INIT;
extern const std::string FLAG_INFO;
extern const std::string FLAG_ERROR;
extern const std::string FLAG_WARN;
extern const std::string FLAG_FRAMEWORK;
extern const std::string FLAG_EVOLVE;
extern const std::string FLAG_DETAILS;
extern const std::string FLAG_BEGIN;
extern const std::string FLAG_END;
extern const std::string FLAG_RESULT;