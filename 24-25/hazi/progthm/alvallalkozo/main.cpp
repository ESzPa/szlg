#include <iostream>
#include <vector>

std::vector<int> munka_kiosztas(int N, std::vector<int> hataridok) {
    int ma = 0;
    std::vector<int> kiosztva;

    for (int i = 0; i < N; i++) {
        if (hataridok[i] > ma) {
            ma++;
            kiosztva.push_back(i+1);
        }
    }

    return kiosztva;
}

int main(void) {
    int N, _;
    std::vector<int> hataridok;
    std::vector<int> kiosztas;

    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cin >> _;
        hataridok.push_back(_);
    }

    kiosztas = munka_kiosztas(N, hataridok);

    std::cout << kiosztas.size() << '\n';
    for (int i = 0; i < kiosztas.size(); i++) {
        std::cout << kiosztas[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}
