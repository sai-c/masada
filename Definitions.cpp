#include "Definitions.h"

#include <iostream>
#include <fstream>
#include <algorithm>

void Definitions::loadHashes(std::string fileName) {
    std::ifstream input(fileName);
    for(std::string line; getline(input, line);)
    {
        hashes.push_back(line);
    }
}

void Definitions::loadSignatures(std::string fileName) {
    std::ifstream input(fileName);
    for(std::string line; getline(input, line);)
    {
        signatures.push_back(line);
    }
}

bool Definitions::checkHash(std::string signature) {
   return std::find(this->hashes.begin(), this->hashes.end(), signature) != this->hashes.end();
}

std::vector<std::string> Definitions::getSignatures() {
   return this->signatures;
}

Definitions::Definitions(std::string hashesPath, std::string sigsPath) {
    loadSignatures(sigsPath);
    loadHashes(hashesPath);
}
