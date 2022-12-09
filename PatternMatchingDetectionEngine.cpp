#include "PatternMatchingDetectionEngine.h"
#include <string>
#include <climits>
#include <fstream>
#include <iostream>

bool PatternMatchingDetectionEngine::checkFile(std::string filePath)
{

    auto signatures = hashDefinitions_.getSignatures();
    std::ifstream openfile(filePath, std::ios::binary | std::ios::ate);
    std::vector<char> data;

    if (openfile.is_open())
    {
        std::streampos file_size = openfile.tellg();
        if (file_size == 0)
        {
            perror("file is empty");
            return false;
        }
        data.resize(file_size);
        openfile.seekg(0, std::ios::beg);
        openfile.read((char *)data.data(), file_size);
        openfile.close();
    }
    else
    {
        perror("error opening file");
        return false;
    }

    for (std::string sig : signatures)
    {
        if (patternMatch(std::string(data.begin(), data.end()), sig))
        {
            return true;
        }
    }
    return false;
}

bool PatternMatchingDetectionEngine::patternMatch(std::string file, std::string signature)
{
    int m = signature.length();
    int n = file.length();
    int i, j;

    int p = 0;
    int t = 0;
    int h = 1;
    int q = INT_MAX; // used with mod to prevent overflow
    int d = 256;

    for (i = 0; i < m - 1; i++)
    {
        h = (h * d) % q; // hash function
    }

    // calculate hash value for string and pattern
    for (i = 0; i < m; i++)
    {
        p = (d * p + signature[i]) % q;
        t = (d * t + file[i]) % q;
    }

    // find the match
    for (i = 0; i <= n - m; i++)
    {
        if (p == t)
        {
            for (j = 0; j < m; j++)
            {
                if (file[i + j] != signature[j])
                {
                    std::cout << "Values match but characters don't" << std::endl;
                    break;
                }
            }

            if (j == m)
            {
                std::cout << "Pattern is found at position: " << i + 1 << std::endl;
                return true;
            }
        }

        if (i < n - m)
        {
            std::cout << "Calculating next hash value" << std::endl;
            t = (d * (t - file[i] * h) + file[i + m]) % q;

            if (t < 0) // negative numbers
                t = (t + q);
        }
    }

    return false;
}