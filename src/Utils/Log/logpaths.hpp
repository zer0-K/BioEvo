#pragma once

#include "../../PreprocessingDefinitions.hpp"

#include <string>
#include <map>

/**
 * !! since everything is done is build, the path of 'src' or 'log' are '../src' and '../log' !!
*/

extern const std::string LOG_PREFIX;    ///< prefix for log file names
extern const std::string LOG_INFO_SUFFIX;   ///< suffix for the info log file

extern const std::string EXPERIMENT_CLASSICAL_ALGO_SUFFIX;   ///< suffix for classical algo log files
extern const std::string EXPERIMENT_CLASSICAL_ALGO_1;   ///< name of the first classical algo experiment

// the paths begin at the root
extern std::map<const std::string, std::string> pathsmap;


extern std::string get_log_name(std::string* log_suffixes, int nb_suffixes);
extern std::string get_log_name_full_relative_path(std::string* log_suffixes, int nb_suffixes, std::string experiment_name);
