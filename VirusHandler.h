#ifndef VIRUSHANDLER_H
#define VIRUSHANDLER_H

#include <string>

class VirusHandler
{
    public: 
        VirusHandler();
        void handle(std::string filePath);
        ~VirusHandler() = default;
};


#endif
