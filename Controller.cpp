// This file takes in user input (can be later changed to UI), and calls Scanner
#include "Definitions.h"
#include "IDetectionEngine.h"
#include "HashingDetectionEngine.h"
#include "PatternMatchingDetectionEngine.h"
#include "Scanner.h"
#include "Logger.h"
#include "FileVault.h"

#include <thread>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

// TODO: MAKE EVERYTHING CONST/CONSTREF
int main()
{
    FileVault quarantine("quarantine.vault");
    quarantine.remove("test.txt");
    std::cout << quarantine.list().size();

    /*Definitions hashDefinitions("test.txt");
    Logger logger("log.txt");
    std::unique_ptr<IDetectionEngine> quickDetectionEngine = std::make_unique<HashingDetectionEngine>(hashDefinitions);
    std::unique_ptr<IDetectionEngine> fullDetectionEngine = std::make_unique<PatternMatchingDetectionEngine>(hashDefinitions);
    std::shared_ptr<VirusHandler> virusHandler = std::make_shared<VirusHandler>();
    Scanner quickScanner(std::move(quickDetectionEngine), virusHandler);
    Scanner fullScanner(std::move(quickDetectionEngine), virusHandler);
    quickScanner.scan("test/");

    std::thread realTimeScanning {&Scanner::realTimeScan, &quickScanner};
    realTimeScanning.join();

    std::cout << "\n\n\n";*/
}
