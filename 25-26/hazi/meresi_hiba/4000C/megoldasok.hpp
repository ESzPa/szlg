#pragma once

#include <algorithm>
#include <iostream>
#include <numeric>

#include "struct.hpp"

namespace internal {
inline settlement_graph::const_iterator it_from_name(const settlement_graph& graph, const char* name) {
    return std::find_if(graph.begin(), graph.end(),
                        [&name](const settlement& s) { return s.name == name; });
}

inline size_t idx_from_name(const settlement_graph& graph, const char* name) {
    return (std::find_if(graph.begin(), graph.end(),
                         [&name](const settlement& s) { return s.name == name; })) -
           graph.begin();
}
} // namespace internal

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

// 4.
inline size_t total_road_len(const settlement_graph& graph) {
    size_t sum = 0;
    for(size_t from = 0; from < graph.size(); ++from) {
        const auto& set = graph[from];

        for(const auto& road : set.roads) {
            size_t to = road.to;

            if(from < to) {
                sum += road.length;
            }
        }
    }
    return sum;
}

// 5. -> 8.
inline bool is_direct_path(const settlement_graph& graph, const char* name1, const char* name2) {
    auto idx1 = internal::idx_from_name(graph, name1);
    auto idx2 = internal::idx_from_name(graph, name2);

    return std::find_if(graph[idx1].roads.begin(), graph[idx1].roads.end(),
                        [idx2](const road& r) { return r.to == idx2; }) != graph[idx1].roads.end();
}

// 9.
inline size_t distance_of_closest(const settlement_graph& graph, const char* name) {
    size_t idx = internal::idx_from_name(graph, name);
    return std::min_element(graph[idx].roads.begin(), graph[idx].roads.end(),
                            [](const road& ra, const road& rb) { return ra.length < rb.length; })
        ->length;
}

// 10.
inline size_t distance_of_farthest(const settlement_graph& graph, const char* name) {
    size_t idx = internal::idx_from_name(graph, name);
    return std::max_element(graph[idx].roads.begin(), graph[idx].roads.end(),
                            [](const road& ra, const road& rb) { return ra.length < rb.length; })
        ->length;
}

// 11.
inline double avg_road_lengths(const settlement_graph& graph, const char* name) {
    size_t idx = internal::idx_from_name(graph, name);
    size_t sum = std::accumulate(graph[idx].roads.begin(), graph[idx].roads.end(), size_t{0},
                                 [](size_t s, const road& r) { return s + r.length; });
    return static_cast<double>(sum) / graph[idx].roads.size();
}
