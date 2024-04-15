#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

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