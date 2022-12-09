#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>
#include "Definitions.h"
#include "IDetectionEngine.h"
#include "HashingDetectionEngine.h"
#include "PatternMatchingDetectionEngine.h"
#include "Scanner.h"
#include "Logger.h"
#include "Controller.h"
#include "FileVault.h"

class Controller
{
private:
    std::shared_ptr<FileVault> quarantine;
    std::unique_ptr<Definitions> definitions;
    std::shared_ptr<Logger> logger;

public:
    Controller(std::string hashesPath, std::string sigsPath);
    void launchQuickScan(std::string path);
    void launchFullScan(std::string path);
    void launchRealTimeScan(std::string path);
    std::vector<std::string> listQuarantine();
    void unQuarantine(std::string path);
    void deleteQuarantine(std::string path);
    void writeQuarantine();
    std::vector<std::string> getOutput();
    ~Controller() = default;
};

#endif
