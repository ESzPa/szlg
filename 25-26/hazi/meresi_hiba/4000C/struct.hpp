#pragma once

#include <cstddef>
#include <string>
#include <vector>

struct road {
    size_t to;
    size_t length;
    road(size_t to, size_t length) : to(to), length(length) {
    }
};

// shitty struct
struct settlement {
    size_t id; // ???, ignored
    std::string name;
    std::string rank;
    std::string kisterseg;
    size_t area;
    size_t population;
    size_t houses;
    std::vector<road> roads;
};

using settlement_graph = std::vector<settlement>;
