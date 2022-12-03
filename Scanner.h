#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "IDetectionEngine.h"
#include "Definitions.h"

class Scanner
{
private:
    std::vector<std::string> Scanner::getOpenFiles();

public:
    Scanner(detectionEngine) : detectionEngine_(detectionEngine){};
    void Scanner::realTimeScan();
    void Scanner::scan(std::string dir);
    ~Scanner() = default;

    IDetectionEngine detectionEngine_;
};

#endif
