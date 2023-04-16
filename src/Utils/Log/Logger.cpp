#include "Logger.hpp"
#include "logpaths.hpp"

#include <iostream>
#include <ctime>

std::string log_name_full;
std::fstream log_file;


void logger_init(std::string* log_suffixes, int nb_suffixes, std::string experiment_name)
{
    // get log file name and open stream
    log_name_full = get_log_name_full_relative_path(log_suffixes, nb_suffixes, experiment_name);
    log_file.open(log_name_full, std::fstream::in | std::fstream::out | std::fstream::app);

    if(log_file.is_open())
    {
        // write date and time at beginning of log
        time_t now = time(0);
        tm* gmtm = gmtime(&now);
        std::string date_and_time = asctime(gmtm);

        log_file<<"Date and time : "<<date_and_time<<std::endl;
        log_file<<"Beginning of "<<experiment_name<<std::endl;
        log_file.flush();
    }
    else
    {
       std::cout<<"Unable to open file"<<std::endl;
    }
}

void logger_write(int log_level, std::string text)
{
    if(LOG_LEVEL > log_level)
    {
        if(log_file.is_open())
        {
            text = FLAG_LOG_LEVEL(log_level) + text;
            log_file<<text<<std::endl;
            log_file.flush();
        }
        else
        {
            std::cout<<"File "<<log_name_full<<" not opened, cannot write in it properly"<<std::endl;
            std::cout<<"Text to write : "<<text<<std::endl;
        }
    }
}

void logger_end()
{
    if(log_file.is_open())
    {
        log_file<<"End"<<std::endl;
        log_file.flush();
        log_file.close();
    }
    else
    {
        std::cout<<"File "<<log_name_full<<" not opened, cannot end logger properly"<<std::endl;
    } 
}