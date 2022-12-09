#include "Scanner.h"

#include <vector>
#include <filesystem>
#include <string>
#include <chrono>
#include <iostream>

std::vector<std::string> Scanner::getOpenFiles()
{
    char buffer[128];
    std::vector<std::string> openFiles;
    std::string command("lsof | egrep 'REG'  | tr -s ' ' | cut -d' ' -f 9 | grep test");

    FILE *pipe = popen(command.c_str(), "r");

    while (!feof(pipe))
    {
        if (fgets(buffer, 128, pipe) != NULL)
            openFiles.push_back(buffer);
    }

    pclose(pipe);
    return openFiles;
}

bool Scanner::handleFile(std::string filePath)
{
    bool result = detectionEngine_->checkFile(filePath);
    if (result)
    {
        virusHandler_->quarantine(filePath);
    }
    return result;
}

void Scanner::realTimeScan()
{
    auto openFiles = Scanner::getOpenFiles();
    for (std::string &filePath : openFiles)
    {
        Scanner::handleFile(filePath);
        logger_->write("realtime.txt", "Scanned " + filePath);
    }
}

void Scanner::scan(std::string dir)
{
    int scanned = 0;
    int quarantined = 0;
    auto t1 = std::chrono::high_resolution_clock::now();
    for (const auto &item : std::filesystem::recursive_directory_iterator(dir))
    {
        if (item.is_regular_file() && !item.is_symlink())
        {
            bool result = Scanner::handleFile(item.path());
            quarantined += result;
            scanned += 1;
        }
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> t_ans = t2 - t1;
    logger_->write("log.txt", "Scanned: " + std::to_string(scanned) + "\nQuarantined: " + std::to_string(quarantined) + "\n Time: " + std::to_string(t_ans.count()) + "s");
}
