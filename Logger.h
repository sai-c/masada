#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Logger
{
    private:
        std::ofstream logFile;

    public: 
        Logger(std::string fileName);
        void write(std::string message);
        ~Logger();
};


#endif
