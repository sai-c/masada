#include "Definitions.h"

#include <iostream>
#include <fstream>
#include <algorithm>

void Definitions::loadSignatures(std::string fileName) {
    std::ifstream input(fileName);
    for(std::string line; getline(input, line);)
    {
        hashes.push_back(line);
    }
}

bool Definitions::checkSignature(std::string signature) {
   return std::find(this->hashes.begin(), this->hashes.end(), signature) != this->hashes.end();
}

std::vector<std::string> Definitions::getSignatures() {
   return this->hashes;
}

Definitions::Definitions(std::string fileName) {
    loadSignatures(fileName);
}
