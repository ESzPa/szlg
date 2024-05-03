#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <unordered_map>


class Student{
    public:
        int sorszam;
        std::string csapat;
        int helyezes;
        int ev;
        std::string helyszin;
};

std::vector<Student> Beolvasas(const char* filename){
    std::vector<Student> students;
    std::ifstream file(filename);
    std::string line;
    while(getline(file, line)){
        std::stringstream sstream(line);
        Student student;
        std::string field;
        getline(sstream, field, '\t');
        student.sorszam = std::stoi(field); 
        getline(sstream, student.csapat, '\t');
        getline(sstream, field, '\t');
        student.helyezes = std::stoi(field); 
        getline(sstream, field, '\t');
        student.sorszam = std::stoi(field); 
        getline(sstream, student.helyszin, '\t');
        students.push_back(student);
    }
    file.close();
    return students;
}

int main(){
    std::vector<Student> students = Beolvasas("input.txt");

    return 0;
}