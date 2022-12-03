// This file takes in user input (can be later changed to UI), and calls Scanner
#include "Definitions.h"
#include "IDetectionEngine.h"
#include "HashingDetectionEngine.h"
#include "PatternMatchingDetectionEngine.h"
#include "Scanner.h"
#include "Logger.h"

#include <thread>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

int main()
{
    Definitions hashDefinitions("test.txt");
    Logger logger("log.txt");
    std::unique_ptr<IDetectionEngine> quickDetectionEngine = std::make_unique<HashingDetectionEngine>(hashDefinitions);
    std::unique_ptr<IDetectionEngine> fullDetectionEngine = std::make_unique<PatternMatchingDetectionEngine>(hashDefinitions);
    std::unique_ptr<VirusHandler> virusHandler = std::make_unique<VirusHandler>();
    Scanner virusScanner(std::move(fullDetectionEngine), std::move(virusHandler));
    virusScanner.scan("test/");
}