#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>

class Sor{
    public:
        int sorszam;
        std::string csapat;
        int helyezes;
        int ev;
        std::string helyszin;

    Sor() : sorszam(0), csapat(""), helyezes(0), ev(0), helyszin("") {}

    Sor(int s, const std::string& c, int h, int e, const std::string& he)
        : sorszam(s), csapat(c), helyezes(h), ev(e), helyszin(he) {}

    bool operator==(const Sor& other) const {
        return sorszam == other.sorszam &&
               csapat == other.csapat &&
               helyezes == other.helyezes &&
               ev == other.ev &&
               helyszin == other.helyszin;
    }
};

struct des {
    bool operator()(const std::string& a, const std::string& b) const {
        return a > b; 
    }
};

namespace std {
    template <>
    struct hash<Sor> {
        size_t operator()(const Sor& sor) const {
            size_t h1 = hash<int>()(sor.sorszam);
            size_t h2 = hash<std::string>()(sor.csapat);
            size_t h3 = hash<int>()(sor.helyezes);
            size_t h4 = hash<int>()(sor.ev);
            size_t h5 = hash<std::string>()(sor.helyszin);
            return h1 ^ h2 ^ h3 ^ h4 ^ h5; // Combine the hash values
        }
    };
}

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
    std::cout << "-------------------------------------\n";
}

std::vector<Sor> Feladat7_12(std::vector<Sor> sorok, int year){
    std::vector<Sor> returnsorok;
    for(Sor s : sorok){
        if(s.ev >= year && s.ev <= year + 9){
            returnsorok.push_back(s);
        }
    }
    return returnsorok;
}

void runFeladat7_12(std::vector<Sor> sorok, int num, int year){
    std::vector<Sor> fsorok = Feladat7_12(sorok, year);
    std::cout << "Feladat " << num << ":\n";
    for(Sor s : fsorok){
        std::cout << s.csapat << ": " << s.ev << "\n";
    }
    std::cout << "-------------------------------------\n";
}

int Feladat13_18(std::vector<Sor> sorok, std::string country){
    int count = 0;
    for(Sor s : sorok){
        if(s.csapat == country){
            count++;
        }
    }
    return count;
}

void runFeladat13_18(std::vector<Sor> sorok, int num, std::string country){
    int count = Feladat13_18(sorok, country);
    std::cout << "Feladat " << num << ":\n";
    std::cout << country << ": " << count << "\n";
    std::cout << "-------------------------------------\n";
}

std::string Feladat19_23(std::vector<Sor> sorok, int year){
    int i = 0;
    while(i < sorok.size()-1){
        ++i;
    }
    return sorok[i].csapat;
}

void runFeladat19_23(std::vector<Sor> sorok, int num, int year){
    std::cout << "Feladat " << num << ": " << Feladat19_23(sorok, year) << '\n';
}

int Feladat24_30(std::vector<Sor> sorok, std::string country){
    int count = 0;
    for(Sor s : sorok){
        if(s.csapat == country && s.helyezes == 2){
            count++;
        }
    }
    return count;
}

void runFeladat24_30(std::vector<Sor> sorok, int num, std::string country){
    std::cout << "Feladat " << num << ": " << country << '\n';
}

int Feladat31(std::vector<Sor> sorok){
    int earliest = 3000;
    for(Sor s : sorok){
        if(s.ev < earliest){
            earliest = s.ev;
        }
    }
    return earliest;
}

int Feladat32_36(std::vector<Sor> sorok, std::string country){
    int count = 0;
    for(Sor s : sorok){
        if(s.csapat == country && s.helyezes == 1){
            count++;
        }
    }
    return count;
}

void runFeladat32_36__43(std::vector<Sor> sorok, int num, std::string country){
    std::cout << "Feladat " << num << ": " << Feladat32_36(sorok, country) << '\n';
}

int Feladat37_42(std::vector<Sor> sorok, std::string country){
    int best = 420;
    for(Sor s : sorok){
        if(s.helyezes < best && s.csapat == country){
            best = s.helyezes;
        }
    }
    return best;
}

void runFeladat37_42(std::vector<Sor> sorok, int num, std::string country){
    std::cout << "Feladat " << num << ": " << Feladat37_42(sorok, country) << '\n';
}

std::vector<Sor> Feladat44_49(std::vector<Sor> sorok, std::string country){
    std::vector<Sor> returnsorok;
    for(Sor s : sorok){
        if(country == s.helyszin){
            returnsorok.push_back(s);
        }
    }
    return returnsorok;
}

void runFeladat44_49(std::vector<Sor> sorok, int num, std::string country){
    std::vector<Sor> fsorok = Feladat44_49(sorok, country);
    std::cout << "Feladat " << num << ": ";
    for(Sor s : fsorok){
        std::cout << s.csapat << ", ";
    }
    std::cout << '\n';
}

bool invector(std::vector<int> v, int num){
    int i = 0;
    while(i < v.size() && v[i] != num){
        ++i;
    }
    return i < v.size();
}

std::vector<Sor> Feladat50_52(std::vector<Sor> sorok, std::string country){
    std::vector<int> temp;
    std::vector<Sor> returnsorok;
    for(Sor s : sorok){
        if(s.csapat == country && s.helyezes <= 3){
            temp.push_back(s.ev);
        }
    }
    for(Sor s : sorok){
        if(s.helyezes == 1 && invector(temp, s.ev)){
            returnsorok.push_back(s);
        }
    }
    return returnsorok;
}

void runFeladat50_52(std::vector<Sor> sorok, int num, std::string country){
    std::vector<Sor> tempsorok = Feladat50_52(sorok, country);
    std::cout << "Feladat " << num << ":\n";
    for(Sor s : tempsorok){
        std::cout << s.csapat << " (" << s.ev << ")\n";
    }
}

std::vector<Sor> Feladat53_57(std::vector<Sor> sorok, std::string country){
    std::vector<int> tempsorok;
    std::vector<Sor> returnsorok;
    for(Sor s : sorok){
        if(s.helyezes <= 2 && s.csapat == country){
            tempsorok.push_back(s.ev);
        }
    }
    for(Sor s : sorok){
        if(s.csapat != country && s.helyezes <= 2 && invector(tempsorok, s.ev)){
            returnsorok.push_back(s);
        }
    }
    return returnsorok;
}

void runFeladat53_57(std::vector<Sor> sorok, int num, std::string country){
    std::vector<Sor> _;
    std::cout << "Feladat " << num << ":\n";
    for(Sor s : _){
        std::cout << s.csapat << " (" << s.ev << ")\n";
    }
}

Sor Feladat58(std::vector<Sor> sorok){
    std::unordered_map<std::string, int> vbwinners;
    for(Sor s : sorok){
        if(s.helyezes == 1){
            vbwinners[s.csapat]++;
        }
        if(vbwinners[s.csapat] > 1){
            return s;
        }
    }
}

Sor Feladat59(std::vector<Sor> sorok){
    std::unordered_map<std::string, int> vbcountries;
    std::vector<int> years;
    for(Sor s : sorok){
        !invector(years, s.ev) ? vbcountries[s.helyszin]++ : false;
        if(vbcountries[s.helyszin] > 1){
            return s;
        }
        years.push_back(s.ev);
    }
}

std::pair<Sor, int> Feladat60_2(std::vector<Sor> sorok, int num){
    std::map<Sor, int, des> helyezes;
    for(Sor s : sorok){
        if(s.helyezes == num){
            helyezes[s]++;
        }
    }
    std::pair<Sor, int> ret = {helyezes.begin()->first, helyezes.begin()->second};
    return ret;
}

std::pair<Sor, int> Feladat61(std::vector<Sor> sorok){
    std::map<Sor, int, des> helyszin;
    for(Sor s : sorok){
        helyszin[s]++;
    }
    std::pair<Sor, int> ret = {helyszin.begin()->first, helyszin.begin()->second};
    return ret;
}

std::map<Sor, int> Feladat63(std::vector<Sor> sorok){
    std::map<Sor, int> orszag;
    for(Sor s : sorok){
        orszag[s]++;
    }
    return orszag;
}

std::vector<Sor> Feladat64_5(std::vector<Sor> sorok){
    std::unordered_map<Sor, int> map;
    std::vector<Sor> ret;
    for(Sor s : sorok){
        map[s]++;
    }
    for(std::pair<Sor, int> p : map){
        ret.push_back(p.first);
    }
    return ret;
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
    runFeladat7_12(sorok, 7, 1930);
    runFeladat7_12(sorok, 8, 1940);
    runFeladat7_12(sorok, 9, 1950);
    runFeladat7_12(sorok, 10, 1960);
    runFeladat7_12(sorok, 11, 1970);
    runFeladat7_12(sorok, 12, 1980);
    runFeladat13_18(sorok, 13, "Magyarország");
    runFeladat13_18(sorok, 14, "Anglia");
    runFeladat13_18(sorok, 15, "Chile");
    runFeladat13_18(sorok, 16, "Peru");
    runFeladat13_18(sorok, 17, "Mongólia");
    std::cin >> str;
    runFeladat13_18(sorok, 18, str);
    runFeladat19_23(sorok, 19, 1930);
    runFeladat19_23(sorok, 20, 1940);
    runFeladat19_23(sorok, 21, 1950);
    runFeladat19_23(sorok, 22, 1960);
    runFeladat19_23(sorok, 23, 1970);
    runFeladat24_30(sorok, 24, "Magyarország");
    runFeladat24_30(sorok, 25, "Mongólia");
    runFeladat24_30(sorok, 26, "Svájc");
    runFeladat24_30(sorok, 27, "Brazília");
    runFeladat24_30(sorok, 28, "Németország");
    runFeladat24_30(sorok, 29, "Argentína");
    std::cin >> str;
    runFeladat24_30(sorok, 30, str);
    std::cout << "Feladat 31: " << Feladat31(sorok) << '\n';
    runFeladat32_36__43(sorok, 32, "Magyarország");
    runFeladat32_36__43(sorok, 33, "Mongólia");
    runFeladat32_36__43(sorok, 34, "Svájc");
    runFeladat32_36__43(sorok, 35, "Brazíla");
    runFeladat32_36__43(sorok, 36, "Argentína");
    runFeladat37_42(sorok, 37, "Magyarország");
    runFeladat37_42(sorok, 38, "Mongólia");
    runFeladat37_42(sorok, 39, "Svájc");
    runFeladat37_42(sorok, 40, "Brazília");
    runFeladat37_42(sorok, 41, "Argentína");
    std::cin >> str;
    runFeladat37_42(sorok, 42, str);
    std::cin >> str;
    runFeladat32_36__43(sorok, 43, str);
    runFeladat44_49(sorok, 44, "Anglia");
    runFeladat44_49(sorok, 45, "Magyarország");
    runFeladat44_49(sorok, 46, "Németország");
    runFeladat44_49(sorok, 47, "Brazília");
    runFeladat44_49(sorok, 48, "Egyesült Államok");
    std::cin >> str;
    runFeladat44_49(sorok, 49, str);
    runFeladat50_52(sorok, 50, "Brazília");
    runFeladat50_52(sorok, 51, "Argentína");
    runFeladat50_52(sorok, 52, "Magyarország");
    runFeladat53_57(sorok, 53, "Magyarország");
    runFeladat53_57(sorok, 54, "Mongólia");
    runFeladat53_57(sorok, 55, "Svájc");
    runFeladat53_57(sorok, 56, "Barzília"); //Így van a feladatban :)
    std::cin >> str;
    runFeladat53_57(sorok, 57, str);
    std::cout << "Feladat 58: " << Feladat58(sorok).csapat << '\n';
    std::cout << "Feladat 59: " << Feladat59(sorok).helyszin << '\n';
    auto s = Feladat60_2(sorok, 1);
    std::cout << "Feladat 60: " << s.first.csapat << ", " << s.second << '\n';
    s = Feladat61(sorok);
    std::cout << "Feladat 61: " << s.first.csapat << ", " << s.second << '\n';
    auto s = Feladat60_2(sorok, 2);
    std::cout << "Feladat 62: " << s.first.csapat << ", " << s.second << '\n';
    std::map<Sor, int> s2 = Feladat63(sorok);
    std::cout << "Feladat 63:\n";
    for(std::pair<Sor, int> p : s2)
    {
        std::cout << p.first.csapat << ": " << p.second << '\n';
    } 
    auto s3 = Feladat64_5(sorok);
    std::cout << "Feladat 64:\n";
    for(Sor s : s3){
        std::cout << s.csapat << '\n';
    }
    std::cout << "Feladat 65:\n";
    for(Sor s : s3){
        std::cout << s.csapat << '\n';
    }

    return 0;
}