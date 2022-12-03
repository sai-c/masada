#ifndef IDETECTIONENGINE_H
#define IDETECTIONENGINE_H

#include <string>

class IDetectionEngine
{
public:
    virtual ~IDetectionEngine(){};
    virtual bool checkFile(std::string filePath) = 0;
};

#endif