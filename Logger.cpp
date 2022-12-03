#include "Logger.h"

Logger::Logger(std::string fileName) {
    this->logFile.open("filename");
}

Logger::write(std::string message) {
    this->logFile << message;
}

Logger::~Logger() {
    logFile.close();
}