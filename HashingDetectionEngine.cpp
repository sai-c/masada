#include "HashingDetectionEngine.h"
#include <string>
#include <iostream>
#include <string.h>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <array>

const int TOTAL_WORD_LISTS = 449;

std::string toFiveDigits(int i){
    if (i > 9999){
        return "" + std::to_string(i);
    } else if (i > 999){
        return "0" + std::to_string(i);
    } else if (i > 99){
        return "00" + std::to_string(i);
    } else if (i > 9){
        return "000" + std::to_string(i);
    } else {
        return "0000" + std::to_string(i);
    }
}

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

void download(){
    for (int i = 0; i <= TOTAL_WORD_LISTS; i++) {
        std::string num = toFiveDigits(i);
        std::ifstream ifile;
        ifile.open("VirusList/VirusShare_" + num + ".md5");
        if(!ifile){
            std::cout << "Downloading Word Lists " + num + "/00449 (" + std::to_string((100.0/TOTAL_WORD_LISTS)*i) + "%)" << '\r' << std::flush;
            system(("wget -q -P VirusList https://virusshare.com/hashfiles/VirusShare_" + num + ".md5").c_str());
        }
        ifile.close();
    }
    printf("\n\033[1;32mDownload finished!\n");
}

int scan(std::string file) {
    std::ifstream ifile;
    ifile.open(file);
    if (ifile) {
        int scanned = 0;
        std::string md5sum = exec(("md5sum " + file).c_str()).substr(0, 32);
        std::cout << "MD5 hash: " << md5sum << std::endl;
        for (int i = 0; i <= TOTAL_WORD_LISTS; i++) {
            std::string num = toFiveDigits(i);
            std::ifstream wfile;
            wfile.open("VirusList/VirusShare_" + num + ".md5");
            if (wfile.is_open()) {
                std::string md5_hash;
                while (std::getline(wfile, md5_hash)){
                    std::cout << "Scanning file... " + std::to_string(scanned) + "/35258368 (" + std::to_string((100.0/35258368)*scanned) + "%)" << '\r' << std::flush;
                    if (md5sum == md5_hash) return 2;
                    scanned++;
                }
                wfile.close();
            }
        }
        ifile.close();
        return 1;
    } else {
        ifile.close();
        return 0;
    }
}

bool HashingDetectionEngine::checkFile(std::string filePath) {

    hashDefinitions_.checkSignature("test");
    
    download();
    int res = scan(filePath);
    switch(res) {
        case 0:
            std::cout << "File does not exist. Please specify a valid file and try again." << std::endl;
            return false;
        case 1:
            std::cout << "File was NOT found on the virus list. Opening this file may be safe." << std::endl;
            return false;
        case 2:
            std::cout << "File WAS found on the virus list. Please delete the file." << std::endl;
            return true;
    }
    return false;
}