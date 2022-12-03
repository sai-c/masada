#ifndef HASHINGDETECTIONENGINE_H
#define HASHINGDETECTIONENGINE_H

#include "IDetectionEngine.h"
#include "Definitions.h"

class HashingDetectionEngine: public IDetectionEngine 
{
public:
    HashingDetectionEngine(Definitions hashDefinitions) : hashDefinitions_(hashDefinitions){};
    ~HashingDetectionEngine(){};
    bool checkFile(std::string filePath);

private:
    Definitions hashDefinitions_;
};

#endif