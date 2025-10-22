//
// Author: Ertinger-Szukk Péter
// Description: Orgonasíp-rendezés
// Deadline: 2025-10-10
// Language: C++17
//
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

void orgonasip_rendez(std::vector<int>& list) {
    // Szepen sorrendbe tesszuk
    std::sort(list.begin(), list.end());
    // Csinalunk egy ideiglenes listat ahova rendezunk
    std::vector<int> temp(list.size());
    // Magic
    temp[list.size()/2] = list.back();
    // Vegigmegyunk az elemeken
    for(int i = 0; i < list.size()-1; ++i){
        // Helyukre tesszuk az elemeket
        temp[i%2 ? list.size()-1-i/2 : i/2] = list[i];
    }
    // Betesszuk az ideiglenes listat az eredeti helyere
    // Copy(O(n)) helyett, moveoljuk (O(1))
    list = std::move(temp);
}

int main(void) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist (0, 99);

    std::vector<int> list;
    for(int i = 0; i < 10; ++i){
        list.push_back(dist(gen));
    }

    auto printvec = [](const std::vector<int>& v){
        for (int x : v) std::cout << x << " ";
        std::cout << "\n";
    };

    printvec(list);
    orgonasip_rendez(list);
    printvec(list);

    return 0;
}
