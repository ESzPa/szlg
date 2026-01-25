#pragma once

#include <iostream>

#include "struct.hpp"

// 1.
inline void print_graphviz(const settlement_graph& graph) {
    std::cout << "graph csongrad {\n"
              << "\tlayout=neato;\n"
              << "\tnode [\n"
              << "\t\tfontsize=40\n"
              << "\t];\n";
    for(size_t from = 0; from < graph.size(); ++from) {
        const auto& set = graph[from];

        for(const auto& road : set.roads) {
            size_t to = road.to;

            if(from < to) {
                std::cout << "\t\"" << set.name << "\" -- \"" << graph[to].name
                          << "\" [len=" << static_cast<double>(road.length) / 12.0 << "];\n";
            }
        }
    }
    std::cout << '}';
}
