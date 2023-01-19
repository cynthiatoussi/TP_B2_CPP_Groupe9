
#include <iostream>
#include <Windows.h>
#include <ctime>

std::string extension;
time_t temps_passe;
std::string ancien_fichier;

int main() {
    std::cout << "Entrer l'extension du fichier pour comparer (sans '.'): ";
    std::cin >> extension;

    // Je recherche le fichier avec l'extension souhait�
    HANDLE hFind = FindFirstFile(("*." + extension).c_str(), &fd);
    if(hFind != INVALID_HANDLE_VALUE) {
        do {
            if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                std::string nom_fichier = fd.cFileName;
                FILETIME ft = fd.ftLastWriteTime;
                time_t temps = (((__int64) ft.dwHighDateTime) << 32) + ft.dwLowDateTime;

                // je v�rifie si le fichier en cours est plus ancien que le pr�c�dent
                if(ancien_fichier.empty() || difftime(temps, temps_passe) < 0) {
                    temps_passe = temps;
                    ancien_fichier = nom_fichier;
                }
            }
        } while(FindNextFile(hFind, &fd));
        FindClose(hFind);
    } else {
        std::cout << "pas de fichier trouv� avec l'extension " << extension << std::endl;
    }

    // Supprimer l'ancien fichier
    if(!ancien_fichier.empty()) {
        std::cout << "Supprimer ancien fichier: " << ancien_fichier << std::endl;
        DeleteFile(ancien_fichier.c_str());
    }

    return 0;
}

