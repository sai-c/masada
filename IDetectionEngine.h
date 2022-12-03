class IDetectionEngine
{
public:
    virtual ~IDetectionEngine(){};
    virtual int checkFile() = 0;
};
