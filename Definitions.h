#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <string>
#include <vector>

class Definitions
{
    private:
        std::vector<std::string> hashes;
        void loadSignatures(std::string fileName);

    public: 
        Definitions(std::string fileName);
        std::vector<std::string> getSignatures();
        ~Definitions() = default;
};


#endif
