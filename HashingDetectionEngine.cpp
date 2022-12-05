#include "HashingDetectionEngine.h"
#include <string>
#include <iostream>
#include <string.h>
#include <fstream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
using namespace std;

int TOTAL_WORD_LISTS = 449;

string toFiveDigits(int i){
    if (i > 9999){
        return "" + to_string(i);
    } else if (i > 999){
        return "0" + to_string(i);
    } else if (i > 99){
        return "00" + to_string(i);
    } else if (i > 9){
        return "000" + to_string(i);
    } else {
        return "0000" + to_string(i);
    }
}

string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

void download(){
    for (int i = 0; i <= TOTAL_WORD_LISTS; i++) {
        string num = toFiveDigits(i);
        ifstream ifile;
        ifile.open("VirusList/VirusShare_" + num + ".md5");
        if(!ifile){
            cout << "Downloading Word Lists " + num + "/00449 (" + to_string((100.0/TOTAL_WORD_LISTS)*i) + "%)" << '\r' << flush;
            system(("wget -q -P VirusList https://virusshare.com/hashfiles/VirusShare_" + num + ".md5").c_str());
        }
        ifile.close();
    }
    printf("\n\033[1;32mDownload finished!\n");
}

int scan(string file) {
    ifstream ifile;
    ifile.open(file);
    if (ifile) {
        int scanned = 0;
        string md5sum = exec(("md5sum " + file).c_str()).substr(0, 32);
        cout << "MD5 hash: " << md5sum << endl;
        for (int i = 0; i <= TOTAL_WORD_LISTS; i++) {
            string num = toFiveDigits(i);
            ifstream wfile;
            wfile.open("VirusList/VirusShare_" + num + ".md5");
            if (wfile.is_open()) {
                string md5_hash;
                while (getline(wfile, md5_hash)){
                    cout << "Scanning file... " + to_string(scanned) + "/35258368 (" + to_string((100.0/35258368)*scanned) + "%)" << '\r' << flush;
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
    int res = scan(filePath);
    switch(res) {
        case 0:
            cout << "File does not exist. Please specify a valid file and try again." << endl;
            return false;
        case 1:
            cout << "File was NOT found on the virus list. Opening this file may be safe." << endl;
            return false;
        case 2:
            cout << "File WAS found on the virus list. Please delete the file." << endl;
            return true;
    }
    return false;
}