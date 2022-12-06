#include "Scanner.h"

#include <vector>
#include <filesystem>
#include <string>
#include <iostream>

std::vector<std::string> Scanner::getOpenFiles() {
    char buffer[128];
    std::vector<std::string> openFiles;
    std::string command("lsof / | egrep 'REG'  | tr -s ' ' | cut -d' ' -f 9");

    FILE* pipe = popen(command.c_str(), "r");

    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            openFiles.push_back(buffer);
    }

    pclose(pipe);
    return openFiles;
}

void Scanner::handleFile(std::string filePath) {
    bool result = detectionEngine_->checkFile(filePath);
    if (result) {
        virusHandler_->quarantine(filePath);
    }
}

void Scanner::realTimeScan() {
    auto openFiles = Scanner::getOpenFiles();
    for (std::string& filePath: openFiles) {
        Scanner::handleFile(filePath);
    }
}

// return somethign gui just runs loops and says output in text box
void Scanner::scan(std::string dir) {
    for (const auto& item : std::filesystem::recursive_directory_iterator(dir))
    {
        if (item.is_regular_file() && !item.is_symlink())
        {
            Scanner::handleFile(item.path());
        }
    }    
}
