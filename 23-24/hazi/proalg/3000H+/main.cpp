#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cmath>

int feladat1(std::vector<int> input);
int feladat2(std::vector<int> input);
int feladat3(std::vector<int> input);
int feladat4(std::vector<int> input);
void feladat5(std::vector<int> input);
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


    std::cout << "1. Feladat: " << feladat1(input) << "\n";
    std::cout << "2. Feladat: " << feladat2(input) << "\n";
    std::cout << "3. Feladat: " << feladat3(input) << "\n";
    std::cout << "4. Feladat: " << feladat4(input) << "\n";
    std::cout << "5. Feladat: "; feladat5(input); std::cout << "\n";
    std::cout << "6. Feladat: " << feladat6(input) << "\n";
    std::cout << "7. Feladat: " << feladat7(input) << "\n";
    std::cout << "8. Feladat: " << feladat8(input) << "\n";
    std::cout << "9. Feladat: " << feladat9(input) << "\n";
    std::cout << "10. Feladat: " << feladat10(input) << "\n";
    std::cout << "11. Feladat: "; feladat11(input, m); std::cout << "\n";
    return 0;
}

int feladat1(std::vector<int> input){
    for(int i = input.size()-1; i >= 0; --i){
        if(std::sqrt(input[i]) == std::floor(std::sqrt(input[i]))){
            return input[i];
        }
    }
    return -2;
}

int feladat2(std::vector<int> input){
    for(int i = 0; i < input.size()-1; ++i){
        if(std::cbrt(input[i]) == std::floor(std::cbrt(input[i]))){
            return i;
        }
    }
    return -1;
}

int feladat3(std::vector<int> input){
    int sum = 0;
    for(int e : input){
        sum += e;
    }
    return sum/input.size();
}

int feladat4(std::vector<int> input){
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

void feladat5(std::vector<int> input){
    for(int e : input){
        if(std::sqrt(e) == std::floor(std::sqrt(e))){
            std::cout << std::sqrt(e) << ", ";
        }
    }
}

int feladat6(std::vector<int> input){
    for(int i = 2; i < input.size()-1; ++i){
        if(input[i] < 0 && input[i-1] == 0 && input[i-2] == 0){
            return 1;
        }
    }
    return 0;
}

int feladat7(std::vector<int> input){
    return input.size();
}

int feladat8(std::vector<int> input){
    for(int e : input){
        if(e <= 0 || e >= 100){
            return 0;
        }
    }
    return 1;
}

int feladat9(std::vector<int> input){
    int monoton = input[0];
    for(int e : input){
        if(e < monoton){
            return 0;
        }
    }
    return 1;
}

int feladat10(std::vector<int> input){
    int i = 0;
    while (i < input.size() && __builtin_popcount(input[i]) != 1)
    {
        i++;
    }
    return i != input.size();
    
}

void feladat11(std::vector<int> input, int m){
    std::unordered_map<int, std::vector<int>> map;
    for(int i = 0; i < input.size(); ++i){
        map[input[i] % m].push_back(input[i]);
    }
    for(auto e : map){
        std::cout << e.first << ": ";

        int min = e.second[0];
        for(int i = 1; i < e.second.size(); ++i){
            if(min > e.second[i]){
                min = e.second[i];
            }
        }
        int max = e.second[0];
        for(int i = 1; i < e.second.size(); ++i){
            if(max < e.second[i]){
                max = e.second[i];
            }
        }

        std::cout << min << ", " << max << "; ";
    }
}
