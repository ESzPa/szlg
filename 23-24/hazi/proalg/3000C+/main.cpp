#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

bool feladat1(std::vector<int> input);
int feladat2(std::vector<int> input);
int feladat3(std::vector<int> input);
float feladat4(std::vector<int> input);
bool feladat5(std::vector<int> input);
int feladat6(std::vector<int> input);
void feladat7(std::vector<int> input);
bool feladat9(std::vector<int> input);
int feladat10(std::vector<int> input);
void feladat11(std::vector<int> input, int m);

int main(){
    std::ifstream f("input.txt");
    std::vector<int> input;
    int _;
    int count = 0;
    while(f >> _){
        input.push_back(_);
        count++;
    }
    f.close();

    int m;
    std::cin >> m;

    std::cout << "1. Feladat: " << feladat1(input) << "\n";
    std::cout << "2. Feladat: " << feladat2(input) << "\n";
    std::cout << "3. Feladat: " << feladat3(input) << "\n";
    std::cout << "4. Feladat: " << feladat4(input) << "\n";
    std::cout << "5. Feladat: " << feladat5(input) << "\n";
    std::cout << "6. Feladat: " << feladat6(input) << "\n";
    std::cout << "7. Feladat: "; feladat7(input); std::cout << "\n";
    std::cout << "8. Feladat: " << count << "\n";
    std::cout << "9. Feladat: " << feladat9(input) << "\n";
    std::cout << "10. Feladat: " << feladat10(input) << "\n";
    std::cout << "11. Feladat: "; feladat11(input, m); std::cout << "\n";

    return 0;
}

bool feladat1(std::vector<int> input){
    for(int e : input){
        if (e % 100 == 0)
        {
            return true;
        }
    }
    return false;
}

int feladat2(std::vector<int> input){
    for(int i = input.size()-1; i >= 0; --i){
        if(input[i] % 7 == 0){
            return i;
        }
    }
    return -1;
}

int feladat3(std::vector<int> input){
    for(int i = 0; i < input.size(); ++i){
        if(input[i] % 19 == 0){
            return i;
        }
    }
    return -1;
}

float feladat4(std::vector<int> input){
    float sum = 0;
    for(int e : input){
        sum += e;
    }
    return (sum/input.size())*(sum/input.size());
}

bool feladat5(std::vector<int> input){
    for(int e : input){
        if(e <= 19){
            return false;
        }
    }
    return true;
}

int feladat6(std::vector<int> input){
    int count = 0;
    for(int e : input){
        if(e % 19 == 0){
            count++;
        }
    }
    return count;
}

void feladat7(std::vector<int> input){
    for(int e : input){
        if(e % 15 == 0){
            std::cout << e/2 << ", ";
        }
    }
}

bool feladat9(std::vector<int> input){
    int prev = 1;
    for(int e : input){
        if(e >= 0 && prev < 0){
            return true;
        }
        if(e < 0){
            prev = -1;
        }
    }
    return 0;
}

int feladat10(std::vector<int> input){
    int min = 99999;
    for(int e : input){
        if(e < min){
            min = e;
        }
    }
    return min / 2;
}

void feladat11(std::vector<int> input, int m){
    std::unordered_map<int, std::vector<int>> map;
    for(int e : input){
        map[e % m].push_back(e);
    }
    for (auto e : map) {
        std::cout << e.first << ": ";
        for (int value : e.second) {
            std::cout << value << " ";
        }
        std::cout << "|| ";
    }
}