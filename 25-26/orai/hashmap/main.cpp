#include <iostream>
#include <random>

#include "hashmap.hpp"

int main(int argc, char** argv) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 2147483647);

    auto rand = [&dist, &gen]() { return dist(gen); };

    hashmap<int, int> map;

    std::cout << map.size() * map.sizeof_node() << '\n';

    for(int a = 0; a < 32; ++a) {
        for(int i = 0; i < 2048; ++i) {
            map[rand()] = rand();
        }

        std::cout << map.size() * map.sizeof_node() / 1024 << '\n';
    }
    std::cout << "::: " << map.size() << '\n';

    return 0;
}
