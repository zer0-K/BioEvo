#include "logpaths.hpp"

#include <iostream>
#include <fstream>
#include <sys/stat.h>

const std::string LOG_PREFIX = "log_experiment";
const std::string LOG_INFO_SUFFIX = "info";

const std::string EXPERIMENT_CLASSICAL_ALGO_SUFFIX = "classical_algo";
const std::string EXPERIMENT_CLASSICAL_ALGO_1 = "experiment classical algos 1";

// the paths begin at the root
std::map<const std::string, std::string> pathsmap = {
    { EXPERIMENT_CLASSICAL_ALGO_1 , "log/experiments/classical_algos/experiment_1" }
};


std::string get_log_name(std::string* log_suffixes, int nb_prefixes)
{
    if(nb_prefixes == 0)
    {
        return "";
    }

    // build log prefixes
    // each log_name
    std::string* log_names = new std::string[nb_prefixes];

    log_names[0] = LOG_PREFIX + "_" + log_suffixes[0];
    for(int i=1; i<nb_prefixes; i++)
    {
        log_names[i] = log_names[i-1] + "_" + log_suffixes[i];
    }
    std::string log_name = log_names[nb_prefixes-1];

#if DEBUG
    for(int i=0; i<nb_prefixes;i++)
    {
        //std::cout<<"Files with prefix : "<<log_names[i]<<std::endl;
    }
#endif

    // get and set file info (TODO) 
    std::fstream log_file_info;
    std::string log_file_info_name = LOG_PREFIX + "_" + LOG_INFO_SUFFIX + ".log";
    log_file_info.open(log_file_info_name, std::ios::in | std::ios::out);

    if(log_file_info.is_open())
    {
        std::string line;
        while ( getline(log_file_info, line) )
        {
            for(int i=0; i<nb_prefixes; i++)
            {
                // find file info
            }
        }

        log_file_info.close();
    }

    std::string log_relative_path = "../" + pathsmap[EXPERIMENT_CLASSICAL_ALGO_1];
   
    // build file name
    bool exists = true;
    int nb = 0;
    std::string log_full_name;
    std::string log_with_path;
    while(exists)
    {
        struct stat buffer; 
        log_full_name = log_name + "_" + std::to_string(nb) + ".log";
        log_with_path = log_relative_path + "/" + log_full_name;
        if( !stat(log_with_path.c_str(), &buffer) == 0)
        {
            exists = false;

#if VERBOSE || DEBUG
            std::cout<<"Log file "<<log_full_name<<" does not exist"<<std::endl;
#endif
        }

#if VERBOSE || DEBUG
        else
        {
            std::cout<<"Log file "<<log_full_name<<" exists"<<std::endl;
        }
#endif
        nb++;
    }

#if VERBOSE || DEBUG
    std::cout<<"New log file : "<<log_full_name<<std::endl;
#endif
    
    return log_full_name;
}

std::string get_log_name_full_relative_path(std::string* log_suffixes, int nb_suffixes, std::string experiment_name)
{
    // get log file name
    std::string log_name = get_log_name(log_suffixes, nb_suffixes);

    if(pathsmap.count(experiment_name))
    {
        std::string log_relative_path = "../" + pathsmap[experiment_name];
        std::string log_full_name = log_relative_path + "/" + log_name;

        return log_full_name;
    }
    else
    {
#if VERBOSE || DEBUG
        std::cout<<experiment_name<<" does not have an attributed log path.\nTo attribute a log path, ";
        std::cout<<"set it in src/Utils/Log/logpaths/hpp"<<std::endl;
#endif
        return "";
    }    
}