#ifndef FILE_VAULT_H
#define FILE_VAULT_H

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>
#include <string.h>
#include <iostream>
#include <fstream>

class FileVault
{
private:
    std::string archive_name;
    std::string magic{".quarantine\x00", 8};
    struct File
    {
        std::string filename;
        long unsigned filesize;
        std::vector<char> data;
    };
    std::vector<File> files;
    bool change = false;

public:
    std::vector<std::string> list();
    void extract(std::string files);
    void remove(std::string file_str);
    void add(std::string files);
    void write();
    FileVault(std::string fileName);
    ~FileVault();
};

#endif
