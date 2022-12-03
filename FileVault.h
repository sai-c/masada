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
        std::string magic{ ".quarantine\x00", 8 };
        std::string password;
        struct File
        {
            std::string filename;
            long unsigned filesize;
            std::vector<char> data;
        };
        std::vector<File> files;

    public: 
        void extract(std::vector<std::string> files);
        void remove(std::vector<std::string> files);
        void add(std::vector<std::string> files);
        FileVault(std::string archive_name);
        ~FileVault();
};


#endif
