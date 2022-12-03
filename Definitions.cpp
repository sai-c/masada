#include "Definitions.h"

#include <iostream>
#include <fstream>

void Definitions::loadSignatures(std::string fileName) {
    std::ifstream input(fileName);
    for(std::string line; getline(input, line);)
    {
        hashes.push_back(line);
    }
}

std::vector<std::string> Definitions::getSignatures() {
   return this->hashes;
}

Definitions::Definitions(std::string fileName) {
    loadSignatures(fileName);
}
