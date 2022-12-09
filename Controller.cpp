// This file takes in user input (can be later changed to UI), and calls Scanner
#include "Controller.h"
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
    logger = std::make_shared<Logger>();
}

void Controller::launchQuickScan(std::string path) {
    std::unique_ptr<IDetectionEngine> quickDetectionEngine = std::make_unique<HashingDetectionEngine>(*definitions);
    std::shared_ptr<VirusHandler> virusHandler = std::make_shared<VirusHandler>(quarantine);
    Scanner quickScanner(std::move(quickDetectionEngine), virusHandler, logger);
    quickScanner.scan(path);
}
void Controller::launchFullScan(std::string path) {
    std::unique_ptr<IDetectionEngine> fullDetectionEngine = std::make_unique<PatternMatchingDetectionEngine>(*definitions);
    std::shared_ptr<VirusHandler> virusHandler = std::make_shared<VirusHandler>(quarantine);
    Scanner fullScanner(std::move(fullDetectionEngine), virusHandler, logger);
    fullScanner.scan(path);
}
void Controller::launchRealTimeScan(std::string path) {
    std::unique_ptr<IDetectionEngine> quickDetectionEngine = std::make_unique<HashingDetectionEngine>(*definitions);
    std::shared_ptr<VirusHandler> virusHandler = std::make_shared<VirusHandler>(quarantine);
    Scanner quickScanner(std::move(quickDetectionEngine), virusHandler, logger);
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
void Controller::writeQuarantine() {
    quarantine->write();
}

std::vector<std::string> Controller::getOutput() {
    return logger->get();
}
