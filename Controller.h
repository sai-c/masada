#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>

class Controller
{
    private:
        std::shared_ptr<FileVault> quarantine;
        std::unique_ptr<Definitions> definitions;
        std::unique_ptr<Logger> logger;

    public: 
        Controller(std::string hashesPath, std::string sigsPath);
        void launchQuickScan(std::string path);
        void launchFullScan(std::string path);
        void launchRealTimeScan(std::string path);
        std::vector<std::string> listQuarantine();
        void unQuarantine(std::string path);
        void deleteQuarantine(std::string path);
        ~Controller() = default;
};

#endif
