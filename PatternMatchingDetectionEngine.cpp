#include "PatternMatchingDetectionEngine.h"
#include <string>
#include <iostream>

bool PatternMatchingDetectionEngine::checkFile(std::string filePath) {


    std::string file = filePath;
    std::string signature = "signature";

    //hashDefinitions_.checkSignature("test");
    if (patternMatch(file, signature)) {
        return true;
    }

    return false;
}

bool patternMatch(std::string file, std::string signature) {

    int m = signature.length();
    int n = file.length();
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;
    int q = INT_MAX; //used with mod to prevent overflow
    int d = 256;


    for (i = 0; i < m - 1; i++) {
        h = (h * d) % q; //hash function
    }

    //calculate hash value for string and pattern
    for (i = 0; i < m; i++) {
        p = (d * p + signature[i]) % q; 
        t = (d * t + file[i]) % q;
    }

    //find the match
    for (i = 0; i <= n - m; i++) {
        if (p == t) {
            for (j = 0; j < m; j++) {
                if (file[i + j] != signature[j]) {
                    std::cout << "Values match but characters don't" << std::endl;
                    break;
                }
            }

            if (j == m) {
                std::cout << "Pattern is found at position: " << i + 1 << std::endl;
                return true;
            }
        }

        if (i < n - m) {
            std::cout << "Calculating next hash value" << std::endl;
            t = (d * (t - file[i] * h) + file[i + m]) % q;

            if (t < 0) //negative numbers
                t = (t + q);
        }
    }

    return false;
}