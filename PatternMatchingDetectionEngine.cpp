#include "PatternMatchingDetectionEngine.h"
#include <string>

bool PatternMatchingDetectionEngine::checkFile(std::string filePath) {

    hashDefinitions_.checkSignature("test");
    return true;
}