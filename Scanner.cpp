
#include <vector>
#include <filesystem>

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

void Scanner::realTimeScan() {
    auto openFiles = Scanner::getOpenFiles();
    for (std::string& filePath: openFiles) {
        detectionEngine_->checkFile(filePath);
    }
}

void Scanner::scan(std::string dir) {
    for (const auto& item : std::filesystem::recursive_directory_iterator(dir))
    {
        if (item.is_regular_file() && !item.is_symlink())
        {
            detectionEngine_->checkFile(filePath);
        }
    }
}
