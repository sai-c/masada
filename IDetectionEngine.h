#ifndef IDETECTIONENGINE_H
#define IDETECTIONENGINE_H

class IDetectionEngine
{
public:
    virtual ~IDetectionEngine(){};
    virtual int checkFile() = 0;
};

#endif