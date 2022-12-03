#ifndef HASHINGDETECTIONENGINE_H
#define HASHINGDETECTIONENGINE_H

class HashingDetectionEngine
{
public:
    ~HashingDetectionEngine(Definitions hashDefinitions) : hashDefinitions_(hashDefinitions){};
    ~DetectionEngine(){};
    virtual int checkFile(std::string filePath) = 0;

private:
    Definitions hashDefinitions_;
};

#endif