// This file takes in user input (can be later changed to UI), and calls Scanner
#include "Definitions.h"
#include "IDetectionEngine.h"
#include "HashingDetectionEngine.h"
#include "Scanner.h"
#include "Logger.h"

#include <thread>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>


int main() {
    Definitions hashDefinitions("test.txt");
    Logger logger("log.txt");
    std::unique_ptr<IDetectionEngine> detectionEngine = std::make_unique<HashingDetectionEngine>();
    Scanner virusScanner(detectionEngine, hashDefinitions);
}