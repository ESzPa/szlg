#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;

#define NEGATIVEINFINITY -999999

int feladat1(vector<int> input);
int feladat2(vector<int> input);
int feladat3(vector<int> input);
int feladat4(vector<int> input);
void feladat5(vector<int> input);
int feladat6(vector<int> input);
int feladat7(vector<int> input);
int feladat8(vector<int> input);
int feladat9(vector<int> input);
int feladat10(vector<int> input);
void feladat11(vector<int> input, int div);

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
    cout << "5. Feladat: "; feladat5(input); cout << "\n";
    cout << "6. Feladat: " << feladat6(input) << "\n";
    cout << "7. Feladat: " << feladat7(input) << "\n";
    cout << "8. Feladat: ~" << feladat8(input) << "\n";
    cout << "9. Feladat: " << feladat9(input) << "\n";
    cout << "10. Feladat: " << feladat10(input) << "\n";
    cin >> _;
    cout << "11. Feladat: "; feladat11(input, _); cout << "\n";

    return 0;
}

int feladat1(vector<int> input){
    return input.size();
}
int feladat2(vector<int> input){
    for(int e : input){
        if(e < 0){ return 1; }
    }
    return 0;
}
int feladat3(vector<int> input){
    int count = 0;
    for(int e : input){
        if(e % 2 == 0){
            count++; 
        } 
    }
    return count;
}
int feladat4(vector<int> input){
    int max = NEGATIVEINFINITY;
    for(int e : input){
        if(e > max){
            max = e;
        }
    }
    return max;
}
void feladat5(vector<int> input){
    for(int e : input){
        if(e % 10 == 0){
            cout << e << ", ";
        }
    }
}
int feladat6(vector<int> input){
    for(int i = 0; i < input.size(); ++i){
        if(input[i] % 29 == 0){
            return i;
        }
    }
    return -1;
}
int feladat7(vector<int> input){
    for(int e : input){
        if(e % 2 == 1){ return 0; }
    }
    return 1;
}
int feladat8(vector<int> input){
    int sum = 0;
    for(int e : input){ sum += e; }
    return sum / (int) input.size();
}
int feladat9(vector<int> input){
    int prev = 1;
    for(int e : input){
        if(prev < 0 && e == 0){
            return 1;
        }
        prev = e;
    }
    return 0;
}
int feladat10(vector<int> input){
    int out = -1;
    for(int e : input){
        if(e % 17 == 0){
            out = e;
        }
    }
    return out;
}
void feladat11(vector<int> input, int div){
    unordered_map<int, int> meinefreunde;
    for(int e : input){
        meinefreunde[e % div]++;
    }
    for(auto e : meinefreunde){
        cout << e.first << ": " << e.second << ", ";
    }
}

