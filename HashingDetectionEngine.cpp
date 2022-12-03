#include "HashingDetectionEngine.h"
#include <string>

bool HashingDetectionEngine::checkFile(std::string filePath) {

    hashDefinitions_.checkSignature("test");
    return true;
}