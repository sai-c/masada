#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <fstream>

#include "IDetectionEngine.h"
#include "VirusHandler.h"
#include "Definitions.h"

class Scanner
{
private:
    std::vector<std::string> getOpenFiles();
    void handleFile(std::string filePath);

public:
    Scanner(std::unique_ptr<IDetectionEngine> detectionEngine, std::shared_ptr<VirusHandler> virusHandler) 
        : detectionEngine_(std::move(detectionEngine)), virusHandler_(std::move(virusHandler)){};
    void realTimeScan();
    void scan(std::string dir);
    ~Scanner() = default;

    std::unique_ptr<IDetectionEngine> detectionEngine_;
    std::shared_ptr<VirusHandler> virusHandler_;
};

#endif
