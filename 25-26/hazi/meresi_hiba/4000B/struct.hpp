#pragma once

#include <cstdint>
#include <string>
#include <vector>

enum class Matcsop : uint8_t { alfa, beta };

enum class Ancsop : uint8_t { first = 1, second = 2, third = 3, fourth = 4 };

enum class Lang : uint8_t { nemet, spanyol };

inline std::string AncsopTeacher(Ancsop ancsop) {
    switch(ancsop) {
        case Ancsop::first: {
            return "Sió";
        }
        case Ancsop::second: {
            return "Bán";
        }
        case Ancsop::third: {
            return "Joó";
        }
        case Ancsop::fourth: {
            return "Kis";
        }
    }
}

struct pupil {
    std::string name;
    Matcsop matcsop;
    Ancsop ancsop;
    Lang nyelv2;
    bool nem;
    int egyuttlakok;
    int testverek;
    std::vector<int> buddies;
};

using netgraph = std::vector<pupil>;
