#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cmath>

void feladat1(std::vector<int> input);
float feladat2(std::vector<int> input);
int feladat3(std::vector<int> input);
int feladat4(std::vector<int> input);
int feladat5(std::vector<int> input);
int feladat6(std::vector<int> input);
int feladat7(std::vector<int> input);
int feladat8(std::vector<int> input);
int feladat9(std::vector<int> input);
int feladat10(std::vector<int> input);
void feladat11(std::vector<int> input, int m);

int main(){
    std::ifstream f("input.txt");
    std::vector<int> input;
    int _;
    int m;
    std::cin >> m;
    while(f >> _){
        input.push_back(_);
    }
    f.close();


    std::cout << "1. Feladat: "; feladat1(input); std::cout << "\n";
    std::cout << "2. Feladat: " << feladat2(input) << "\n";
    std::cout << "3. Feladat: " << feladat3(input) << "\n";
    std::cout << "4. Feladat: " << feladat4(input) << "\n";
    std::cout << "5. Feladat: " << feladat5(input) << "\n";
    std::cout << "6. Feladat: " << feladat6(input) << "\n";
    std::cout << "7. Feladat: " << feladat7(input) << "\n";
    std::cout << "8. Feladat: " << feladat8(input) << "\n";
    std::cout << "9. Feladat: " << feladat9(input) << "\n";
    std::cout << "10. Feladat: " << feladat10(input) << "\n";
    std::cout << "11. Feladat: "; feladat11(input, m); std::cout << "\n";

    return 0;
}

void feladat1(std::vector<int> input){
    for(int e : input){
        if(e % 17 == 0){
            std::cout << e/3 << ", ";
        }
    }
}

float feladat2(std::vector<int> input){
    for(int i = input.size()-1; i >= 0; --i){
        if(input[i] % 9 == 0 || input[i] % 25 == 0){
            return sqrt(input[i]);
        }
    }
    return -2;
}

int feladat3(std::vector<int> input){
    for(int i = 0; i < input.size()-1; ++i){
        if(input[i] % 3 == 0 || input[i] % 5 == 0){
            return i;
        }
    }
    return -1;
}

int feladat4(std::vector<int> input){
    for(int e : input){
        if(e < 0 || e > 20){
            return 0;
        }
    }
    return 1;
}

int feladat5(std::vector<int> input){
    for(int i = 1; i < input.size()-2; ++i){
        if(input[i] < 0 && input[i-1] == 0 && input[i+1] == 0){
            return 1;
        }
    }
    return 0;
}

int feladat6(std::vector<int> input){
    int c = 0;
    for(int e : input){
        if(e % 6 == 0){
            c++;
        }
    }
    return c;
}

int feladat7(std::vector<int> input){
    return input.size();
}

int feladat8(std::vector<int> input){
    int maxt1 = input[0];
    int maxt2;
    for(int e : input){
        if(e > maxt1){
            maxt2 = maxt1;
            maxt1 = e;
        }
    }
    return maxt2;
}

int feladat9(std::vector<int> input){
    for(int e : input){
        if(std::cbrt(e) == std::floor(std::cbrt(e))){
            return 1;
        }
    }
    return 0;
}

int feladat10(std::vector<int> input){
    int mult = 1;
    for(int e : input){
        mult *= e;
    }
    return mult/2;
}

void feladat11(std::vector<int> input, int m){
    std::unordered_map<int, std::vector<int>> map;
    for(int e : input){
        map[e % m].push_back(e);
    }
    for(std::pair<int, std::vector<int>> p : map){
        float average = 0;
        for(int e : p.second){
            average += e;
        }
        average /= p.second.size();
        std::cout << p.first << ": " << average << "; ";
    }
}