#ifndef VIRUSHANDLER_H
#define VIRUSHANDLER_H

#include <string>
#include "FileVault.h"
#include <memory>

class VirusHandler
{
public:
    VirusHandler(std::shared_ptr<FileVault> quarantine) : quarantine_(std::move(quarantine)){};
    void quarantine(std::string filePath);
    ~VirusHandler() = default;

private:
    std::shared_ptr<FileVault> quarantine_;
};

#endif
