#ifndef VIRUSHANDLER_H
#define VIRUSHANDLER_H

#include <string>

class VirusHandler
{
    public: 
        VirusHandler() {};
        void quarantine(std::string filePath);
        ~VirusHandler() = default;
};


#endif
