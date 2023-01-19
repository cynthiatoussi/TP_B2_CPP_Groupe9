
#include <iostream>
#include <fstream>
#include <map>
#include <dirent.h>
#include <algorithm>

using namespace std;

class Config {

private:
    string folder;
    string extension;
    time_t date;

public:
    Config(string folder, string extension, time_t date)
    : folder(folder), extension(extension), date(date) {}
    //getters
    string getFolder() { return folder; }
    string getExtension() { return extension; }
    time_t getDate() { return date; }
    //setters
    void setFolder(string folder) { this->folder = folder; }
    void setExtension(string extension) { this->extension = extension; }
    void setDate(time_t date) { this->date = date; }
    void sortAndStore() {
        DIR* dir;
        struct dirent* ent;
        map<string, vector<string>> files;
        if ((dir = opendir(this->folder.c_str())) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                string fileName = ent->d_name;
                if (fileName == "." || fileName == "..") {
                    continue;
                }
                string ext = fileName.substr(fileName.find_last_of(".") + 1);
                if (ext == this->extension) {
                    files[ext].push_back(fileName);
                }
            }
            closedir(dir);
            ofstream outputFile("Keyce.csv");
            outputFile << "File Name, Extension" << endl;
            for (const auto& [ext, fileList] : files) {
                sort(fileList.begin(), fileList.end());
                for (const auto& file : fileList) {
                    outputFile << file << "," << ext << endl;
                }
            }
            outputFile.close();
        } else {
            cerr << "Failed to open directory " << this->folder << endl;
        }
    }
};
