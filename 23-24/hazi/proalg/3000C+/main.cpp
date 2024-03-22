#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

int feladat1(std::vector<int> input);
int feladat2(std::vector<int> input);
int feladat3(std::vector<int> input);
int feladat4(std::vector<int> input);
int feladat5(std::vector<int> input);
int feladat6(std::vector<int> input);
int feladat7(std::vector<int> input);
int feladat8(std::vector<int> input);
int feladat9(std::vector<int> input);
int feladat10(std::vector<int> input);
int feladat11(std::vector<int> input);

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
    std::cout << "9. Feladat: " << feladat9(input) << "\n";
    std::cout << "10. Feladat: " << feladat10(input) << "\n";
    std::cout << "11. Feladat: " << feladat11(input) << "\n";

    return 0;
}


