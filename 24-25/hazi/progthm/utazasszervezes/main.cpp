#include <iostream>
#include <vector>
#include <sstream>

bool van_szabad(std::vector<int>& emberek, int nap, int m){
    for(int i = 0; i < emberek.size(); i++){
        if(nap >= emberek[i]){
            emberek[i] = nap + m;
            return true;
        }
    }
    return false;
}

int megoldas(int n, int k, int m, int c, std::vector<int> igenyek){
    std::vector<int> emberek(n, 0);
    size_t teljesitett = 0;

    for(int igeny : igenyek){
        if(van_szabad(emberek, igeny, m)){
            teljesitett++;
        }
    }

    return teljesitett;
}

int main(void){
    int n, k, m, c;
    int _;

    std::cin >> n >> k >> m >> c;
    std::vector<int> igenyek(c);
    for(int i = 0; i < c; i++){
        std::cin >> igenyek[i];
    }

    std::cout << megoldas(n, k, m, c, igenyek);

    return 0;
}