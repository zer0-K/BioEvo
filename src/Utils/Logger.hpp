#pragma once

#include <string>
#include <iostream>
#include <fstream>

/**
 * @brief logger
*/
class Logger
{
public:
    static Logger* l;

private:

    Logger()
    {
        
    }

public:
    static void write(std::string txt)
    {
        if(l == NULL)
            l = new Logger();

        std::ofstream logfile;
        logfile.open(LOG_FILE_DEFAULT, std::ios::out | std::ios::app);
        logfile << txt << std::endl;
        logfile.close();
    }

};

inline Logger* Logger::l = NULL;