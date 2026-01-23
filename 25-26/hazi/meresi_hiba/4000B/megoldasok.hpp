#pragma once

#include <algorithm>
#include <iostream>
#include <queue>

#include "struct.hpp"

// 1.
inline void print_graphviz(const netgraph& graph) {
    std::cout << "digraph BUDDIES {\n";

    for(int i = 0; i < graph.size(); ++i) {
        const auto& e = graph[i];
        for(const auto& bud : e.buddies) {
            std::cout << '\t' << i << " -> " << bud << ";\n";
        }
    }

    std::cout << "}\n";
}

// 2. & 3.
inline bool are_buddies(const netgraph& graph, const std::string& name1, const std::string& name2) {
    auto it1 =
        std::find_if(graph.begin(), graph.end(), [&name1](const pupil& p) { return p.name == name1; });

    auto it2 =
        std::find_if(graph.begin(), graph.end(), [&name2](const pupil& p) { return p.name == name2; });

    size_t idx2 = it2 - graph.begin();

    return std::binary_search(it1->buddies.begin(), it1->buddies.end(), idx2);
}

// 5. & 6.
inline ssize_t buddy_count(const netgraph& graph, const std::string& name) {
    auto it =
        std::find_if(graph.begin(), graph.end(), [&name](const pupil& p) { return p.name == name; });

    return (it == graph.end() ? -1 : it->buddies.size());
}

// 7. & 8.
template <typename Func>
inline std::string buddy_count_cmp(const netgraph& graph, Func cmp) {
    pupil p = graph[0];
    for(size_t i = 1; i < graph.size(); ++i) {
        if(cmp(p.buddies.size(), graph[i].buddies.size())) {
            p = graph[i];
        }
    }
    return p.name;
}

// 9. & 10.
template <typename Func>
inline size_t buddy_count_with_property(const netgraph& graph, const std::string& name, Func check) {
    auto it =
        std::find_if(graph.begin(), graph.end(), [&name](const pupil& p) { return p.name == name; });

    size_t count = 0;
    for(const auto& idx : it->buddies) {
        if(check(graph, idx)) {
            ++count;
        }
    }

    return count;
}

// 11. & 12.
inline std::vector<pupil> buddies_of(const netgraph& graph, const std::string& name) {
    auto it =
        std::find_if(graph.begin(), graph.end(), [&name](const pupil& p) { return p.name == name; });

    std::vector<pupil> buddies;
    for(auto idx : it->buddies) {
        buddies.push_back(graph[idx]);
    }

    return buddies;
}

// 13.
inline std::vector<pupil> indirect_buddies(const netgraph& graph, const std::string& name) {
    std::vector<pupil> res;
    auto it =
        std::find_if(graph.begin(), graph.end(), [&name](const pupil& p) { return p.name == name; });

    std::vector<bool> visited(graph.size(), false);
    std::queue<size_t> q;

    size_t src = it - graph.begin();
    visited[src] = true;
    q.push(src);

    while(!q.empty()) {
        size_t curr = q.front();
        q.pop();
        res.push_back(graph[curr]);

        for(auto x : graph[curr].buddies) {
            if(!visited[x]) {
                visited[x] = true;
                q.push(x);
            }
        }
    }

    return res;
}

// 15.
inline bool indirect_path_search(const netgraph& graph, int curr, int target, std::vector<bool>& visited,
                                 std::vector<int>& path) {
    visited[curr] = true;
    path.push_back(curr);

    if(curr == target) {
        return true;
    }

    for(auto v : graph[curr].buddies) {
        if(!visited[v]) {
            if(indirect_path_search(graph, v, target, visited, path)) {
                return true;
            }
        }
    }

    path.pop_back();
    return false;
}

// 16.
template <typename Func>
inline std::vector<int> all_reachable_if(const netgraph& graph, const std::string& name, Func func) {
    auto it =
        std::find_if(graph.begin(), graph.end(), [&name](const pupil& p) { return p.name == name; });

    std::queue<int> q;
    std::vector<bool> visited(graph.size(), false);
    std::vector<int> res;

    int src = it - graph.begin();
    visited[src] = true;
    q.push(src);

    while(!q.empty()) {
        int curr = q.front();
        q.pop();
        res.push_back(curr);

        for(auto b : graph[curr].buddies) {
            if(!visited[b]) {
                visited[b] = true;
                q.push(b);
            }
        }
    }

    for(auto b : res) {
        if(!func(it - graph.begin(), b)) {
            res.erase(std::remove(res.begin(), res.end(), b), res.end());
        }
    }

    return res;
}
