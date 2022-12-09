#include "Logger.h"

Logger::Logger() {
    this->recentLog=std::make_unique<std::vector<std::string>>();
}

void Logger::write(std::string fileName, std::string message) {
    std::ofstream logFile;
    logFile.open(fileName);
    logFile << message;
    logFile.close();
    this->recentLog->push_back(message);
}

std::vector<std::string> Logger::get() {
    std::vector<std::string> output(*this->recentLog);
    this->recentLog->clear();
    return output;
}

Logger::~Logger() {
}