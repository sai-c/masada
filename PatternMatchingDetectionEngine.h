#ifndef PATTERNMATCHINGDETECTIONENGINE_H
#define PATTERNMATCHINGDETECTIONENGINE_H

#include "IDetectionEngine.h"
#include "Definitions.h"

class PatternMatchingDetectionEngine : public IDetectionEngine
{
public:
    PatternMatchingDetectionEngine(Definitions hashDefinitions) : hashDefinitions_(hashDefinitions){};
    ~PatternMatchingDetectionEngine(){};
    bool checkFile(std::string filePath);
    bool patternMatch(std::string file, std::string signature);

private:
    Definitions hashDefinitions_;
};

#endif