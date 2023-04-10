#pragma once

#include <string>
#include <fstream>

extern std::string log_name_full;   ///< full relative path of the log file
extern std::fstream log_file;   ///< file stream to write/read on

/**
* @brief Init the logger
* 
* @param[in] log_suffixes suffixes to identify the log file (order counts)
* @param[in] nb_suffixes number of suffixes
* @param[in] experiment_name name of the experiment to find the related log file
*/
extern void logger_init(std::string* log_suffixes, int nb_suffixes, std::string experiment_name);

/**
* @brief write text in the log
* 
* @param[in] flags flags of the text (for ex : 'DEBUG', 'INFO', 'ERROR',...)
* @param[in] nb_flags number of flags
* @param[in] text text to write in the logs
*/
extern void logger_write(std::string* flags, int nb_flags, std::string text);

/**
* @brief end the logger (close file,...)
*/
extern void logger_end();
