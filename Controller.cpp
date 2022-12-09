// This file takes in user input (can be later changed to UI), and calls Scanner
#include "Definitions.h"
#include "IDetectionEngine.h"
#include "HashingDetectionEngine.h"
#include "PatternMatchingDetectionEngine.h"
#include "Scanner.h"
#include "Logger.h"
#include "Controller.h"
#include "FileVault.h"

#include <thread>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

// TODO: MAKE EVERYTHING CONST/CONSTREF

Controller::Controller(std::string hashesPath, std::string sigsPath) {
    definitions = std::make_unique<Definitions>(hashesPath, sigsPath);
    quarantine = std::make_shared<FileVault>("quarantine.vault");
    logger = std::make_unique<Logger>("log.txt");
}

void Controller::launchQuickScan(std::string path) {
    std::unique_ptr<IDetectionEngine> quickDetectionEngine = std::make_unique<HashingDetectionEngine>(*definitions);
    std::shared_ptr<VirusHandler> virusHandler = std::make_shared<VirusHandler>(quarantine);
    Scanner quickScanner(std::move(quickDetectionEngine), virusHandler);
    quickScanner.scan(path);
}
void Controller::launchFullScan(std::string path) {
    std::unique_ptr<IDetectionEngine> fullDetectionEngine = std::make_unique<PatternMatchingDetectionEngine>(*definitions);
    std::shared_ptr<VirusHandler> virusHandler = std::make_shared<VirusHandler>(quarantine);
    Scanner fullScanner(std::move(fullDetectionEngine), virusHandler);
    fullScanner.scan(path);
}
void Controller::launchRealTimeScan(std::string path) {
    std::unique_ptr<IDetectionEngine> quickDetectionEngine = std::make_unique<HashingDetectionEngine>(*definitions);
    std::shared_ptr<VirusHandler> virusHandler = std::make_shared<VirusHandler>(quarantine);
    Scanner quickScanner(std::move(quickDetectionEngine), virusHandler);
    quickScanner.scan(path);
    std::thread realTimeScanning {&Scanner::realTimeScan, &quickScanner};
    realTimeScanning.join();

}
std::vector<std::string> Controller::listQuarantine() {
    return quarantine->list();
}
void Controller::unQuarantine(std::string path) {
    quarantine->extract(path);
    quarantine->remove(path);
}
void Controller::deleteQuarantine(std::string path) {
    quarantine->remove(path);
}

int main()
{
    Controller c("hashes.txt", "sigs.txt");
    c.launchFullScan("test");
}
