#pragma once

#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>

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

inline void print_vec(std::vector<settlement_graph::const_iterator> vec) {
    for(const auto& it : vec) {
        std::cout << it->name << ", ";
    }
}

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

// 13.
inline size_t idx_max_neighbours(const settlement_graph& graph) {
    size_t max_idx = 0;
    for(size_t i = 1; i < graph.size(); ++i) {
        if(graph[max_idx].roads.size() < graph[i].roads.size()) {
            max_idx = i;
        }
    }
    return max_idx;
}

// 14.
inline std::vector<settlement_graph::const_iterator>
it_settlements_with_neighbours(const settlement_graph& graph, size_t count) {
    std::vector<settlement_graph::const_iterator> res;
    for(auto it = graph.begin(); it != graph.end(); ++it) {
        if(it->roads.size() == count) {
            res.push_back(it);
        }
    }
    return res;
}

// 15. -> 17.
inline std::vector<settlement_graph::const_iterator>
shortest_path(const settlement_graph& graph, const char* name_from, const char* name_target) {
    size_t idx_from = internal::idx_from_name(graph, name_from);
    size_t idx_target = internal::idx_from_name(graph, name_target);

    std::vector<ssize_t> dist(graph.size(), -1);
    std::vector<ssize_t> parent(graph.size(), -1);
    std::queue<size_t> q;

    dist[idx_from] = 0;
    q.push(idx_from);

    bool f = false;
    while(!q.empty() && !f) {
        size_t cur = q.front();
        q.pop();

        for(const auto& r : graph.at(cur).roads) {
            if(dist[r.to] == -1) {
                dist[r.to] = dist[cur] + 1;
                parent[r.to] = cur;
                q.push(r.to);

                if(r.to == idx_target) {
                    f = true;
                    break;
                }
            }
        }
    }

    std::vector<settlement_graph::const_iterator> path;
    if(dist[idx_target] == -1) {
        return path;
    }

    for(ssize_t idx = idx_target; idx != -1; idx = parent[idx]) {
        path.push_back(graph.begin() + idx);
    }

    std::reverse(path.begin(), path.end());
    return path;
}

// 18. -> 19.
inline std::vector<settlement_graph::const_iterator>
dijkstra(const settlement_graph& graph, const char* name_start, const char* name_target) {
    size_t start = internal::idx_from_name(graph, name_start);
    size_t target = internal::idx_from_name(graph, name_target);

    const size_t N = graph.size();
    constexpr size_t INF = std::numeric_limits<size_t>::max();

    std::vector<size_t> dist(N, INF);
    std::vector<ssize_t> parent(N, -1);

    using state = std::pair<size_t, size_t>;
    std::priority_queue<state, std::vector<state>, std::greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if(d > dist[u]) {
            continue;
        }

        if(u == target) {
            break;
        }

        for(const auto& r : graph.at(u).roads) {
            if(dist[r.to] > dist[u] + r.length) {
                dist[r.to] = dist[u] + r.length;
                parent[r.to] = (ssize_t)u;
                pq.push({dist[r.to], r.to});
            }
        }
    }

    std::vector<settlement_graph::const_iterator> path;
    if(dist[target] == INF) {
        return path;
    }

    for(ssize_t idx = (ssize_t)target; idx != -1; idx = parent[idx]) {
        path.push_back(graph.begin() + idx);
    }

    std::reverse(path.begin(), path.end());
    return path;
}

// 20. ->21.
inline settlement_graph::const_iterator dijkstra_by_kisterseg(const settlement_graph& graph,
                                                              const char* name_start,
                                                              const std::string& kisterseg) {
    size_t start = internal::idx_from_name(graph, name_start);

    const size_t N = graph.size();
    constexpr size_t INF = std::numeric_limits<size_t>::max();

    std::vector<size_t> dist(N, INF);
    std::vector<ssize_t> parent(N, -1);

    using state = std::pair<size_t, size_t>;
    std::priority_queue<state, std::vector<state>, std::greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    size_t last;
    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        last = u;

        if(d > dist[u]) {
            continue;
        }

        if(graph[u].kisterseg == kisterseg) {
            break;
        }

        for(const auto& r : graph.at(u).roads) {
            if(dist[r.to] > dist[u] + r.length) {
                dist[r.to] = dist[u] + r.length;
                parent[r.to] = (ssize_t)u;
                pq.push({dist[r.to], r.to});
            }
        }
    }

    return last + graph.begin();
}

// 22. -> 23.
inline std::vector<settlement_graph::const_iterator>
dijkstra_collection(const settlement_graph& graph, const char* name_start, size_t distance) {
    std::vector<settlement_graph::const_iterator> res;
    size_t start = internal::idx_from_name(graph, name_start);

    const size_t N = graph.size();
    constexpr size_t INF = std::numeric_limits<size_t>::max();

    std::vector<size_t> dist(N, INF);
    std::vector<ssize_t> parent(N, -1);

    using state = std::pair<size_t, size_t>;
    std::priority_queue<state, std::vector<state>, std::greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if(d > dist[u]) {
            continue;
        }

        if(dist[u] > distance) {
            break;
        }

        res.push_back(graph.begin() + u);

        for(const auto& r : graph.at(u).roads) {
            if(dist[r.to] > dist[u] + r.length) {
                dist[r.to] = dist[u] + r.length;
                parent[r.to] = (ssize_t)u;
                pq.push({dist[r.to], r.to});
            }
        }
    }

    return res;
}

// 24.
inline std::vector<settlement_graph::const_iterator> dijkstra_avoid(const settlement_graph& graph,
                                                                    const char* name_start,
                                                                    const char* name_target,
                                                                    const std::string& kisterseg) {
    size_t start = internal::idx_from_name(graph, name_start);
    size_t target = internal::idx_from_name(graph, name_target);

    const size_t N = graph.size();
    constexpr size_t INF = std::numeric_limits<size_t>::max();

    std::vector<size_t> dist(N, INF);
    std::vector<ssize_t> parent(N, -1);

    using state = std::pair<size_t, size_t>;
    std::priority_queue<state, std::vector<state>, std::greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if(d > dist[u]) {
            continue;
        }

        if(u == target) {
            break;
        }

        for(const auto& r : graph.at(u).roads) {
            if(graph.at(r.to).kisterseg == kisterseg) {
                continue;
            }
            if(dist[r.to] > dist[u] + r.length) {
                dist[r.to] = dist[u] + r.length;
                parent[r.to] = (ssize_t)u;
                pq.push({dist[r.to], r.to});
            }
        }
    }

    std::vector<settlement_graph::const_iterator> path;
    if(dist[target] == INF) {
        return path;
    }

    for(ssize_t idx = (ssize_t)target; idx != -1; idx = parent[idx]) {
        path.push_back(graph.begin() + idx);
    }

    std::reverse(path.begin(), path.end());
    return path;
}
