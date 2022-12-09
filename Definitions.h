#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <string>
#include <vector>

class Definitions
{
    private:
        std::vector<std::string> hashes;
        std::vector<std::string> signatures;
        void loadSignatures(std::string fileName);
        void loadHashes(std::string fileName);

    public: 
        Definitions(std::string hashesPath, std::string sigsPath);
        std::vector<std::string> getSignatures();
        bool checkHash(std::string signature);
        ~Definitions() = default;
};


#endif
