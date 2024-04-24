#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <unordered_map>

struct Student{
    int id;
    std::string name;
    std::string mathinfo;
    std::string english;
    std::string secondlang;
    std::string sex;
    int housemates;
    int siblings;
};

int Feladat1(std::vector<Student> students);
int Feladat2_3(std::vector<Student> students, std::string sex);
std::vector<std::string> Feladat4_5_6_7(std::vector<Student> students, int num);
std::vector<std::string> Feladat8_9(std::vector<Student> students);
int Feladat10_11(std::vector<Student> students, char num);
int Feladat12_13(std::vector<Student> students, std::string alfabeta);
int Feladat14_15_16_17(std::vector<Student> students, std::string alfabeta, std::string sex);
int Feladat18_19_20(std::vector<Student> students, std::string secondlang);
int Feladat21(std::vector<Student> students);
std::string Feladat22(std::vector<Student> students);
std::vector<std::string> Feladat23(std::vector<Student> students);
std::vector<std::string> Feladat24(std::vector<Student> students);
int Feladat25(std::vector<Student> students);
std::vector<std::string> Feladat26_27_28_29_30(std::vector<Student> students, std::string name);
std::string Feladat31(std::vector<Student> students);
std::vector<std::string> Feladat32(std::vector<Student> students, std::string lang);
int Feladat33(std::vector<Student> students);
int Feladat34(std::vector<Student> students);
std::unordered_map<std::string, int> Feladat35(std::vector<Student> students);
std::unordered_map<int, int> Feladat36(std::vector<Student> students);
void StudentPrint(Student student);
std::vector<Student> Beolvasas(const char* filename);

int main(){
    std::vector<Student> students = Beolvasas("input.txt");

    std::cout << "Feladat 1: " << Feladat1(students) << '\n';
    std::cout << "Feladat 2: " << Feladat2_3(students, "F") << '\n';
    std::cout << "Feladat 3: " << Feladat2_3(students, "L") << '\n';
    std::cout << "Feladat 4: " << Feladat4_5_6_7(students, 1).size() << '\n';
    std::cout << "Feladat 5: ";
    for(std::string name : Feladat4_5_6_7(students, 1)){
        std::cout << name << ", ";
    }
    std::cout << '\n';
    std::cout << "Feladat 6: " << Feladat4_5_6_7(students, 2).size() << '\n';
    std::cout << "Feladat 7: ";
    for(std::string name : Feladat4_5_6_7(students, 2)){
        std::cout << name << ", ";
    }
    std::cout << '\n';
    std::cout << "Feladat 8: " << Feladat8_9(students).size() << '\n';
    std::cout << "Feladat 9: ";
    for(std::string name : Feladat8_9(students)){
        std::cout << name << ", ";
    }
    std::cout << '\n';
    std::cout << "Feladat 10: " << Feladat10_11(students, '1') << '\n';
    std::cout << "Feladat 11: " << Feladat10_11(students, '2') << '\n';
    std::cout << "Feladat 12: " << Feladat12_13(students, "alfa") << '\n';
    std::cout << "Feladat 13: " << Feladat12_13(students, "beta") << '\n';
    std::cout << "Feladat 14: " << Feladat14_15_16_17(students, "alfa", "F") << '\n';
    std::cout << "Feladat 15: " << Feladat14_15_16_17(students, "beta", "F") << '\n';
    std::cout << "Feladat 16: " << Feladat14_15_16_17(students, "alfa", "L") << '\n';
    std::cout << "Feladat 17: " << Feladat14_15_16_17(students, "beta", "L") << '\n';
    std::cout << "Feladat 18: " << Feladat18_19_20(students, "orosz") << '\n';
    std::cout << "Feladat 19: " << Feladat18_19_20(students, "olasz") << '\n';
    std::cout << "Feladat 20: " << Feladat18_19_20(students, "spanyol") << '\n';
    std::cout << "Feladat 21: " << Feladat21(students) << '\n';
    std::cout << "Feladat 22: " << Feladat22(students) << '\n';
    std::cout << "Feladat 23: ";
    for(std::string name : Feladat23(students)){
        std::cout << name << ", ";
    }
    std::cout << '\n';
    std::cout << "Feladat 24: ";
    for(std::string name : Feladat24(students)){
        std::cout << name << ", ";
    }
    std::cout << '\n';
    std::cout << "Feladat 25: " << Feladat25(students) << '\n';
    std::cout << "Feladat 26: ";
    for(std::string name : Feladat26_27_28_29_30(students, "Dári Dóra")){
        std::cout << name << ", ";
    }
    std::cout << '\n';
    std::cout << "Feladat 27: ";
    for(std::string name : Feladat26_27_28_29_30(students, "Avon Mór")){
        std::cout << name << ", ";
    }
    std::cout << '\n';
    std::cout << "Feladat 28: ";
    for(std::string name : Feladat26_27_28_29_30(students, "Zúz Mara")){
        std::cout << name << ", ";
    }
    std::cout << '\n';
    std::cout << "Feladat 29: ";
    for(std::string name : Feladat26_27_28_29_30(students, "Citad Ella")){
        std::cout << name << ", ";
    }
    std::cout << '\n';
    std::cout << "Feladat 30: ";
    for(std::string name : Feladat26_27_28_29_30(students, "Hát Izsák")){
        std::cout << name << ", ";
    }
    std::cout << '\n';
    std::cout << "Feladat 31: " << Feladat31(students) << '\n';
    std::cout << "Nyelv: ";
    std::string _;
    std::cin >> _;
    std::cout << "Feladat 32: ";
    for(std::string name : Feladat32(students, _)){
        std::cout << name << ", ";
    }
    std::cout << '\n';
    std::cout << "Feladat 33: " << Feladat33(students) << '\n';
    std::cout << "Feladat 34: " << Feladat34(students) << '\n';
    std::unordered_map<std::string, int> groups1 = Feladat35(students);
    std::cout << "Feladat 35: ";
    for(std::pair<std::string, int> e : groups1){
        std::cout << e.first << ": " << e.second << " || ";
    }
    std::cout << "\n";
    std::unordered_map<int, int> groups2 = Feladat36(students);
    std::cout << "Feladat 36: ";
    for(std::pair<int, int> e : groups2){
        std::cout << e.first << ": " << e.second << " || ";
    }
    std::cout << "\n";

    return 0;
}

int Feladat1(std::vector<Student> students){
    return students.size();
}

int Feladat2_3(std::vector<Student> students, std::string sex){
    int count = 0;
    for(Student s : students){
        if(s.sex == sex) count++;
    }
    return count;
}

std::vector<std::string> Feladat4_5_6_7(std::vector<Student> students, int num){
    std::vector<std::string> names;
    for(Student s : students){
        if(s.siblings > num) names.push_back(s.name);
    }
    return names;
}

std::vector<std::string> Feladat8_9(std::vector<Student> students){
    std::vector<std::string> names;
    for(Student s :students){
        if(s.secondlang == "német") names.push_back(s.name);
    }
    return names;
}

int Feladat10_11(std::vector<Student> students, char num){
    int count = 0;
    for(Student s : students){
        if(s.english[0] == num) count++;
    }
    return count;
}

int Feladat12_13(std::vector<Student> students, std::string alfabeta){
    int count = 0;
    for(Student s : students){
        if(s.mathinfo == alfabeta) count++;
    }
    return count;
}

int Feladat14_15_16_17(std::vector<Student> students, std::string alfabeta, std::string sex){
    int count = 0;
    for(Student s : students){
        if(s.mathinfo == alfabeta && s.sex == sex) count++;
    }
    return count;
}

int Feladat18_19_20(std::vector<Student> students, std::string secondlang){
    for(Student s : students){
        if(s.secondlang == secondlang) return 1;
    }
    return 0;
}

int Feladat21(std::vector<Student> students){
    int max = 0;
    for(Student s : students){
        if(s.housemates > max){
            max = s.housemates;
        }
    }
    return max;
}

std::string Feladat22(std::vector<Student> students){
    int index = 0;
    for(int i = 1; i < students.size()-1; ++i){
        if(students[index].siblings < students[i].siblings){
            index = i;
        }
    }
    return students[index].name;
}

std::vector<std::string> Feladat23(std::vector<Student> students){
    std::vector<std::string> names;
    for(Student s : students){
        if((s.english.substr(0, 1) == "1" || s.english.substr(0, 1) == "2") && s.sex == "L"){
            names.push_back(s.name);
        }
    }
    return names;
}

std::vector<std::string> Feladat24(std::vector<Student> students){
    std::vector<std::string> names;
    for(Student s : students){
        if((s.english.substr(0, 1) == "4" || s.english.substr(0, 1) == "3") && (s.siblings == 0 || s.siblings == 2) && s.sex == "F"){
            names.push_back(s.name);
        }
    }
    return names;
}

int Feladat25(std::vector<Student> students){
    int count = 0;
    for(Student s : students){
        count += std::abs(s.housemates - s.siblings) != 3;
    }
    return count;
}

std::vector<std::string> Feladat26_27_28_29_30(std::vector<Student> students, std::string name){
    std::string ddgroup;
    std::vector<std::string> names;
    for(Student s : students){
        if(s.name == name){
            ddgroup = s.english.substr(0, 1);
            break;
        }
    }
    for(Student s : students){
        if(s.english.substr(0, 1) == ddgroup){
            names.push_back(s.name);
        }
    }
    return names;
}

std::string Feladat31(std::vector<Student> students){
    std::pair<int, std::string> spanyol = {0, "spanyol"}, 
                                nemet = {0, "német"};
    for(Student s : students){
        if(s.secondlang == spanyol.second){
            ++spanyol.first;
        }
        else if(s.secondlang == nemet.second){
            ++nemet.first;
        }
    }
    return (spanyol.first < nemet.first) ? nemet.second : spanyol.second;
}

std::vector<std::string> Feladat32(std::vector<Student> students, std::string lang){
    std::vector<std::string> names;
    for(Student s : students){
        if(s.secondlang == lang){
            names.push_back(s.name);
        }
    }
    return names;
}

int Feladat33(std::vector<Student> students){
    std::vector<std::string> langs;
    for(Student s : students){
        if(std::find(langs.begin(), langs.end(), s.secondlang) == langs.end()){
            langs.push_back(s.secondlang);
        }
    }
    return langs.size();
}

int Feladat34(std::vector<Student> students){
    std::vector<std::string> groups;
    for(Student s : students){
        if(std::find(groups.begin(), groups.end(), s.mathinfo) == groups.end()){
            groups.push_back(s.mathinfo);
        }
    }
    return groups.size();
}

std::unordered_map<std::string, int> Feladat35(std::vector<Student> students){
    std::unordered_map<std::string, int> groupnum;
    for(Student s : students){
        groupnum[s.english]++;
    }
    return groupnum;
}

std::unordered_map<int, int> Feladat36(std::vector<Student> students){
    std::unordered_map<int, int> groupnum;
    for(Student s : students){
        groupnum[s.housemates]++;
    }
    return groupnum;
}

void StudentPrint(Student student){
    std::cout << student.name << " (" << student.sex << "): " << student.id << '\n';
    std::cout << student.mathinfo << '\n';
    std::cout << student.english << " / " << '\n';
    std::cout << student.secondlang << '\n';
    std::cout << student.housemates << '\n';
    std::cout << student.siblings << '\n';
}

std::vector<Student> Beolvasas(const char* filename){
    std::vector<Student> students;
    std::ifstream file(filename);
    std::string line;
    while(getline(file, line)){
        std::stringstream sstream(line);
        Student student;
        std::string field;
        getline(sstream, field, ';');
        student.id = std::stoi(field); 
        getline(sstream, student.name, ';');
        getline(sstream, student.mathinfo, ';');
        getline(sstream, student.english, ';');
        getline(sstream, student.secondlang, ';');
        getline(sstream, student.sex, ';');
        getline(sstream, field, ';');
        student.housemates = std::stoi(field);
        getline(sstream, field, ';');
        student.siblings = std::stoi(field);
        students.push_back(student);
    }
    file.close();
    return students;
}