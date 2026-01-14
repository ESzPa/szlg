#pragma once

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

enum class FATYPE : uint8_t {
    // clang-format off
    BUKK,
    FENYO,
    PLATAN,
    JUHAR,
    TOLGY,
    KORIS,
    VADGESZTENYE,
    EGER,
    HARS,
    GYERTYAN,
    // clang-format on
};

inline FATYPE str_to_fatype(const std::string& str) {
    if(str == "bukk")
        return FATYPE::BUKK;
    if(str == "fenyo")
        return FATYPE::FENYO;
    if(str == "platan")
        return FATYPE::PLATAN;
    if(str == "juhar")
        return FATYPE::JUHAR;
    if(str == "tolgy")
        return FATYPE::TOLGY;
    if(str == "koris")
        return FATYPE::KORIS;
    if(str == "vadgesztenye")
        return FATYPE::VADGESZTENYE;
    if(str == "eger")
        return FATYPE::EGER;
    if(str == "hars")
        return FATYPE::HARS;
    return FATYPE::GYERTYAN;
}

struct FaNode {
    int height;
    FATYPE type;
    std::vector<int> connected;
};

using FaGraph = std::unordered_map<int, FaNode>;

// -- Feladatok --

// 1.
inline void print_graphviz(const FaGraph& graph) {
    std::cout << "digraph FAK {\n";

    for(const auto& fa : graph) {
        for(const auto& con : fa.second.connected) {
            std::cout << '\t';
            std::cout << fa.first << " -> " << con;
            std::cout << '\n';
        }
    }

    std::cout << "}\n";
}

// 2. & 3.
inline bool are_connected(const FaGraph& graph, int x, int y) {
    auto it = graph.find(x);
    if(it == graph.end()) {
        return false;
    }
    const auto& v = it->second.connected;
    return std::find(v.begin(), v.end(), y) != v.end();
}

// 4. & 5. helper
template <typename Func>
inline int terminal_node(const FaGraph& graph, Func comp) {
    for(const auto& node : graph) {
        bool all_higher = true;
        for(const int con : node.second.connected) {
            auto it = graph.find(con);
            if(comp(node.second.height, it->second.height)) {
                all_higher = false;
                break;
            }
        }
        if(all_higher) {
            return node.first;
        }
    }
    return -1;
}

// 4.
inline int low_node(const FaGraph& graph) {
    return terminal_node(graph, [](int a, int b) { return a > b; });
}

// 5.
inline int high_node(const FaGraph& graph) {
    return terminal_node(graph, [](int a, int b) { return a < b; });
}

// 6.
inline int most_popular_node(const FaGraph& graph) {
    int max_id = -1;
    int max_opt = -1;
    for(const auto& node : graph) {
        int options = 0;
        for(const int con : node.second.connected) {
            auto it = graph.find(con);
            options += (node.second.height > it->second.height);
        }
        if(options > max_opt) {
            max_opt = options;
            max_id = node.first;
        }
    }
    return max_id;
}

// 7.
inline std::pair<int, int> steepest_con(const FaGraph& graph) {
    int from_id = -1;
    int to_id = -1;
    int max_steepness = -1;
    for(const auto& node : graph) {
        for(int con : node.second.connected) {
            auto it = graph.find(con);
            int loc_steepness = node.second.height - it->second.height;
            if(max_steepness < loc_steepness) {
                from_id = node.first;
                to_id = con;
                max_steepness = loc_steepness;
            }
        }
    }

    return {from_id, to_id};
}

// 8. & 9.
inline bool is_reachable(const FaGraph& graph, int from_id, int to_id) {
    std::queue<int> q;
    std::unordered_set<int> visited;

    q.push(from_id);
    visited.insert(from_id);

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        if(node == to_id) {
            return true;
        }

        auto it = graph.find(node);
        if(it == graph.end()) {
            continue;
        }

        for(int neighbour : it->second.connected) {
            auto it_neigh = graph.find(neighbour);
            if((it_neigh->second.height < it->second.height) && visited.insert(neighbour).second) {
                q.push(neighbour);
            }
        }
    }

    return false;
}

// 10. & 11. & 12. & 13. & 14. & 17. & 18.
template <typename Func>
inline std::unordered_set<int> all_reachable(const FaGraph& graph, int from_id, Func premise) {
    std::queue<int> q;
    std::unordered_set<int> visited;

    q.push(from_id);
    visited.insert(from_id);

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        auto it = graph.find(node);
        if(it == graph.end()) {
            continue;
        }

        for(int neighbour : it->second.connected) {
            auto it_neigh = graph.find(neighbour);
            if(premise(it->second, it_neigh->second) && visited.insert(neighbour).second) {
                q.push(neighbour);
            }
        }
    }

    return visited;
}

namespace {
inline int helper15(const FaGraph& graph, int node_id, std::unordered_map<int, int>& memo) {
    if(auto it = memo.find(node_id); it != memo.end()) {
        return it->second;
    }

    auto git = graph.find(node_id);
    if(git == graph.end()) {
        return 0;
    }

    const FaNode& node = git->second;

    int best = 1;

    for(int child_id : node.connected) {
        auto cit = graph.find(child_id);
        if(cit == graph.end())
            continue;

        if(cit->second.height >= node.height)
            continue;

        best = std::max(best, 1 + helper15(graph, child_id, memo));
    }

    memo[node_id] = best;
    return best;
};
} // namespace

// 15.
inline int longest_run(const FaGraph& graph, int from_id) {
    std::unordered_map<int, int> memo;
    return helper15(graph, from_id, memo);
}

namespace {
inline int helper16(const FaGraph& graph, int node_id, std::unordered_map<int, int>& memo) {
    if(auto it = memo.find(node_id); it != memo.end())
        return it->second;

    auto git = graph.find(node_id);
    if(git == graph.end())
        return 0;

    const FaNode& node = git->second;
    int best = 0;

    for(int child_id : node.connected) {
        auto cit = graph.find(child_id);
        if(cit == graph.end())
            continue;

        if(cit->second.height >= node.height)
            continue;

        int drop = node.height - cit->second.height;
        best = std::max(best, drop + helper16(graph, child_id, memo));
    }

    memo[node_id] = best;
    return best;
};
} // namespace

// 16.
inline int steepest_from(const FaGraph& graph, int from_id) {
    std::unordered_map<int, int> memo;
    return helper16(graph, from_id, memo);
}

namespace {
inline void helper17_18(const FaGraph& graph, int node_id, FATYPE target_type,
                        std::unordered_set<int>& visited, std::vector<int>& result) {
    if(!visited.insert(node_id).second)
        return;

    auto git = graph.find(node_id);
    if(git == graph.end())
        return;

    const FaNode& node = git->second;

    if(node.type == target_type) {
        result.push_back(node_id);
    }

    for(int child_id : node.connected) {
        auto cit = graph.find(child_id);
        if(cit == graph.end())
            continue;

        if(cit->second.height >= node.height)
            continue;

        helper17_18(graph, child_id, target_type, visited, result);
    }
}
} // namespace

// 17. & 18.
inline std::vector<int> collect_all_type(const FaGraph& graph, int from_id, FATYPE type) {
    std::unordered_set<int> visited;
    std::vector<int> result;
    helper17_18(graph, from_id, type, visited, result);
    return result;
}

// 19. & 20.
// Definetly not stolen
inline std::vector<int> shortest_path(const FaGraph& graph, int from_id, int to_id) {
    std::queue<int> q;
    std::unordered_set<int> visited;
    std::unordered_map<int, int> parent;

    q.push(from_id);
    visited.insert(from_id);
    parent[from_id] = -1;

    while(!q.empty()) {
        int cur = q.front();
        q.pop();

        if(cur == to_id)
            break;

        auto git = graph.find(cur);
        if(git == graph.end())
            continue;

        const FaNode& node = git->second;

        for(int child_id : node.connected) {
            auto cit = graph.find(child_id);
            if(cit == graph.end())
                continue;

            if(cit->second.height >= node.height)
                continue;

            if(visited.insert(child_id).second) {
                parent[child_id] = cur;
                q.push(child_id);
            }
        }
    }

    if(!visited.count(to_id)) {
        return {};
    }

    std::vector<int> path;
    for(int v = to_id; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());
    return path;
}
