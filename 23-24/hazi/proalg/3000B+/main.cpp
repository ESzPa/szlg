#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;

int feladat1(vector<int> input);
int feladat2(vector<int> input);
int feladat3(vector<int> input);
int feladat4(vector<int> input);
float feladat5(vector<int> input);
int feladat6(vector<int> input);
int feladat7(vector<int> input);
int feladat8(vector<int> input);
int feladat9(vector<int> input);
void feladat10(vector<int> input);
void feladat11(vector<int> input, int m);

int main(){
    ifstream f("input.txt");
    vector<int> input;
    int _;
    while(f >> _){
        input.push_back(_);
    }
    f.close();

    cout << "1. Feladat: " << feladat1(input) << "\n";
    cout << "2. Feladat: " << feladat2(input) << "\n";
    cout << "3. Feladat: " << feladat3(input) << "\n";
    cout << "4. Feladat: " << feladat4(input) << "\n";
    cout << "5. Feladat: " << feladat5(input) << "\n";
    cout << "6. Feladat: " << feladat6(input) << "\n";
    cout << "7. Feladat: " << feladat7(input) << "\n";
    cout << "8. Feladat: " << feladat8(input) << "\n";
    cout << "9. Feladat: " << feladat9(input) << "\n";
    cout << "10. Feladat: "; feladat10(input); cout << "\n";
    cout << "11. Feladat: "; feladat11(input); cout << "\n";

    return 0;
}

int feladat1(vector<int> input){
    for(int e : input){
        if(e > 0){ return 1; }
    }
    return 0;
}
int feladat2(vector<int> input){
    return input.size();
}
int feladat3(vector<int> input) {
    int min = 99999999;
    for(int e : input) {
        if(e < min) {
            min = e;
        }
    }
    return min;
}
int feladat4(vector<int> input){
    int i = 0;
    while(i < input.size()){
        if(input[i] % 33 == 0){
            return i;
        }
        ++i;
    }
    return -1;
}
float feladat5(vector<int> input){
    float sum = 0.0f;
    for(int e : input){ sum += e; }
    return (sum/input.size()/2);
}
int feladat6(vector<int> input){
    for(int e : input){
        if(e % 2 != 0){ return 0; }
    }
    return 1;
}
int feladat7(vector<int> input){
    int count = 0;
    for(int e : input){
        if(e % 2 != 0){ count++; }
    }
    return count;
}
int feladat8(vector<int> input){
    int prev = 1;
    for(int e : input){
        if(prev < 0 && e < 0){ return 1; }
        prev = e;
    }
    return 0;
}
int feladat9(vector<int> input){
    int index = -1;
    for(int i = 0; i < input.size(); ++i){
        int e = input[i];
        if(e % 19 == 0){
            index = i;
        }
    }
    return index;
}

void feladat10(vector<int> input){
    for(int e : input){
        if(e%5 == 0){
            cout << e << " ";
        }
    }
}
void feladat11(vector<int> input){
    int m;
    cin >> m;
    unordered_map<int, int> map;
    for(int e : input){
        map[e % m] += e;
    }
    for(auto e : map){
        cout << e.first << ": " << e.second << " || ";
    }
}

