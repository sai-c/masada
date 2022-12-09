#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <fstream>

class Logger
{
private:
    std::unique_ptr<std::vector<std::string>> recentLog;

public:
    Logger();
    void write(std::string fileName, std::string message);
    std::vector<std::string> get();
    ~Logger();
};

#endif
