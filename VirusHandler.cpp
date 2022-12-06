#include "VirusHandler.h"
#include <iostream>

void VirusHandler::quarantine(std::string filePath) {
    std::cerr << filePath.c_str();
    quarantine_->add(filePath);
    quarantine_->write();
    return;
}