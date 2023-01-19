#include <iostream>
#include <string>
#include <ctime>

using namespace std;
class config{

private:
    std::string folder;
    std::string extension;
    std::time_t date;

public:
    config(std::string folder,std::string extension,std::time_t date)
    :folder(folder),extension(extension),date(date)
    //getters
    std::string getfolder(){return folder;}
    std::string getextension(){return extension;}
    std::time_t getdate(){return date;}
    //setters
    void setfolder(std::string folder){this->folder = folder;}
    void setextension(std::string extension){this->extension = extension;}
    void setdate(std::time_t date){this->date = date;}
};
int main(){
//initialise la configuration avec des valeurs
config config("keyce_Drive","csv",std::time(nullptr));
std::cout << "the folder to synchronize is: "<<config.getfolder()<< std::endl;
std::cout << "the extension of files to consider is: "<<config.getextension()<< std::endl;
std::cout << "the date of modification to consider is: "<<ctime(&config.getdate());
return 0;
}
