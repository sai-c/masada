#include "VirusHandler.h"
#include <iostream>
#include <filesystem>

void VirusHandler::quarantine(std::string filePath)
{
    quarantine_->add(filePath);
    quarantine_->write();
    std::filesystem::remove(filePath);
    return;
}