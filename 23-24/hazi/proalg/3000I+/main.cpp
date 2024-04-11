#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>

int feladat1(std::vector<int> input);
int feladat2(std::vector<int> input);
int feladat3(std::vector<int> input);
int feladat4(std::vector<int> input);
int feladat5(std::vector<int> input);
int feladat6(std::vector<int> input);
int feladat7(std::vector<int> input);
int feladat8(std::vector<int> input);
void feladat9(std::vector<int> input);
int feladat10(std::vector<int> input);
void feladat11(std::vector<int> input);

int main(){
    std::ifstream f("input.txt");
    std::vector<int> input;
    int _;
    while(f >> _){
        input.push_back(_);
    }
    f.close();


    std::cout << "1. Feladat: " << feladat1(input) << "\n";
    std::cout << "2. Feladat: " << feladat2(input) << "\n";
    std::cout << "3. Feladat: " << feladat3(input) << "\n";
    std::cout << "4. Feladat: " << feladat4(input) << "\n";
    std::cout << "5. Feladat: " << feladat5(input) << "\n";
    std::cout << "6. Feladat: " << feladat6(input) << "\n";
    std::cout << "7. Feladat: " << feladat7(input) << "\n";
    std::cout << "8. Feladat: " << feladat8(input) << "\n";
    std::cout << "9. Feladat: "; feladat9(input); std::cout << "\n";
    std::cout << "10. Feladat: " << feladat10(input) << "\n";
    std::cout << "11. Feladat: "; feladat11(input); std::cout << "\n";

    return 0;
}

int feladat1(std::vector<int> input){
    for(int i = input.size()-1; i >= 0; --i){
        if(std::cbrt(input[i]) == std::floor(std::cbrt(input[i]))){
            return input[i];
        }
    }
    return 0;
}

int feladat2(std::vector<int> input){
    return input.size();
}

int feladat3(std::vector<int> input){
    int diffadd = 0;
    for(int i = 0; i < input.size()-2; ++i){
        diffadd += input[i] - input[i+1];
    }
    return diffadd;
}

int feladat4(std::vector<int> input){
    for(int i = 0; i < input.size()-1; ++i){
        if(input[i] % i == 0){
            return 1;
        }
    }
    return 0;
}

int feladat5(std::vector<int> input){
    int diff = input[0] - input[1];
    for(int i = 1; i < input.size()-2; ++i){
        if(diff != input[i] - input[i+1]){
            return 0;
        }
    }
    return 1;
}

int feladat6(std::vector<int> input){
    for(int e : input){
        if(sqrt(e) == floor(sqrt(e))){
            return e*e;
        }
    }
    return -1;
}

bool isprime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int feladat7(std::vector<int> input){
    for(int e : input){
        if(isprime(e)){
            return 1;
        }
    }
    return 0;
}

int feladat8(std::vector<int> input){
    for(int e : input){
        if(e < -50 || e > 50){
            return 0;
        }
    }
    return 1;
}

void feladat9(std::vector<int> input){
    for(int e : input){
        if(isprime(e)){
            std::cout << e << ", ";
        }
    }
}

int feladat10(std::vector<int> input){
    int sum = 0;
    for(int e : input){
        sum += e;
    }
    int memory = input[0];
    for(int i = 1; i < input.size()-1; ++i){
        if(abs(input[i] - sum/input.size()) < abs(memory - sum/input.size())){
            memory = input[i];
        }
    }
    return memory;
}

void feladat11(std::vector<int> input, int m){
    std::unordered_map<int, std::vector<int>> map;
    for(int e : input){
        map[e % m].push_back(e);
    }
    for(std::pair<int, std::vector<int>> p : map){
        std::sort(p.second.begin(), p.second.end());
        if(p.second.size() % 2 == 0){
            std::cout << p.first << ": " << (p.second[p.second.size()/2-1] + p.second[p.second.size()/2-1])/2 << "; ";
        }
        else{
            std::cout << p.first << ": " << p.second[p.second.size()/2-1] << "; ";
        }
    }
}