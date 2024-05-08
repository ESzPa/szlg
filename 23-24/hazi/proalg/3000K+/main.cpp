#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <unordered_map>


class Sor{
    public:
        int sorszam;
        std::string csapat;
        int helyezes;
        int ev;
        std::string helyszin;
};

std::vector<Sor> Beolvasas(const char* filename){
    std::vector<Sor> sorok;
    std::ifstream file(filename);
    std::string line;
    while(getline(file, line)){
        std::stringstream sstream(line);
        Sor sor;
        std::string field;
        getline(sstream, field, '\t');
        sor.sorszam = std::stoi(field); 
        getline(sstream, sor.csapat, '\t');
        getline(sstream, field, '\t');
        sor.helyezes = std::stoi(field); 
        getline(sstream, field, '\t');
        sor.ev = std::stoi(field); 
        getline(sstream, sor.helyszin, '\t');
        sorok.push_back(sor);
    }
    file.close();
    return sorok;
}

void StudentPrint(Sor sor){
    std::cout << sor.sorszam << "\n";
    std::cout << sor.csapat << "\n";
    std::cout << sor.helyezes << "\n";
    std::cout << sor.ev << "\n";
    std::cout << sor.helyszin << "\n";
}

std::vector<Sor> Feladat1_6(std::vector<Sor> sorok, std::string country){
    std::vector<Sor> returnsorok;
    for(Sor s : sorok){
        if(s.csapat == country){
            returnsorok.push_back(s);
        }
    }
    return returnsorok;
}

void runFeladat1_6(std::vector<Sor> sorok, int num, std::string country){
    std::vector<Sor> fsorok = Feladat1_6(sorok, country);
    std::cout << "Feladat " << num << ":\n";
    for(Sor s : fsorok){
        std::cout << s.csapat << ": " << s.helyezes << " (" << s.ev << ", " << s.helyszin << ")\n";
    }
}

int main(){
    std::vector<Sor> sorok = Beolvasas("input.txt");

    runFeladat1_6(sorok, 1, "Magyarország");
    runFeladat1_6(sorok, 2, "Anglia");
    runFeladat1_6(sorok, 3, "Chile");
    runFeladat1_6(sorok, 4, "Peru");
    runFeladat1_6(sorok, 5, "Mongólia");
    std::string str;
    std::cin >> str;
    runFeladat1_6(sorok, 6, str);


    return 0;
}