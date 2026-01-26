#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

#include "megoldasok.hpp"
#include "struct.hpp"

settlement_graph parse();

void print_next(std::function<void()> f);

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    settlement_graph graph = parse();

    print_next([&graph]() { /*print_graphviz(graph);*/ }); // 1.
    print_next([&graph]() { std::cout << graph.size(); }); // 2.
    print_next([&graph]() {                                // 3.
        std::cout << std::accumulate(
                         graph.begin(), graph.end(), size_t{0},
                         [](size_t sum, const settlement& s) { return sum + s.roads.size(); }) /
                         2;
    });
    print_next([&graph]() { std::cout << total_road_len(graph); }); // 4.
    print_next(
        [&graph]() { std::cout << std::boolalpha << is_direct_path(graph, "Szeged", "Deszk"); }); // 5.
    print_next([&graph]() {
        std::cout << std::boolalpha << is_direct_path(graph, "Szeged", "Hodmezovasarhely"); // 6.
    });
    print_next(
        [&graph]() { std::cout << std::boolalpha << is_direct_path(graph, "Algyor", "Felgyor"); }); // 7.
    print_next([&graph]() {
        std::cout << std::boolalpha << is_direct_path(graph, "Pusztaszer", "Opusztaszer"); // 8.
    });
    print_next([&graph]() { std::cout << distance_of_closest(graph, "Szeged"); });            // 9.
    print_next([&graph]() { std::cout << distance_of_farthest(graph, "Hodmezovasarhely"); }); // 10.
    print_next([&graph]() { std::cout << avg_road_lengths(graph, "Szeged"); });               // 11.
    print_next(
        [&graph]() { std::cout << internal::it_from_name(graph, "Kiralyhegyes")->roads.size(); }); // 12.
    print_next([&graph]() { std::cout << graph[idx_max_neighbours(graph)].name; });                // 13.
    print_next([&graph]() { print_vec(it_settlements_with_neighbours(graph, 1)); });               // 14.
    print_next([&graph]() { std::cout << shortest_path(graph, "Nagylak", "Szentes").size(); });    // 15.
    print_next([&graph]() { print_vec(shortest_path(graph, "Nagylak", "Szentes")); });             // 16.
    print_next([&graph]() { print_vec(shortest_path(graph, "Roszke", "Eperjes")); });              // 17.
    print_next([&graph]() { print_vec(dijkstra(graph, "Tomorkeny", "Kiszombor")); });              // 18.
    print_next([&graph]() { print_vec(dijkstra(graph, "Baks", "Mindszent")); });                   // 19.
    print_next(
        [&graph]() { std::cout << dijkstra_by_kisterseg(graph, "Szeged", "Szentes")->name; }); // 20.
    print_next(
        [&graph]() { std::cout << dijkstra_by_kisterseg(graph, "Szeged", "Szentes")->name; });   // 21.
    print_next([&graph]() { std::cout << dijkstra_collection(graph, "Szeged", 30000).size(); }); // 22.
    print_next([&graph]() {                                                                      // 23.
        auto g = dijkstra_collection(graph, "Hodmezovasarhely", 40000);
        std::cout << std::accumulate(
            g.begin(), g.end(), size_t{0},
            [](size_t sum, const settlement_graph::const_iterator& it) { return sum + it->population; });
    });
    print_next([&graph]() {
        print_vec(dijkstra_avoid(graph, "Nagymagocs", "Szeged", "Hodmezovasarhelyi")); // 24.
    });

    return 0;
}

settlement_graph parse() {
    settlement_graph graph;

    {
        std::ifstream telepulesek("4000C_telepulesek.tsv");
        if(!telepulesek.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

        std::string line;
        std::getline(telepulesek, line);
        while(std::getline(telepulesek, line)) {
            std::vector<std::string> fields;
            std::stringstream ss(line);
            std::string field;

            while(std::getline(ss, field, '\t')) {
                fields.push_back(field);
            }

            graph.emplace_back(settlement{
                static_cast<size_t>(std::stoi(fields[0])), fields[1], fields[2], fields[3],
                static_cast<size_t>(std::stoi(fields[4])), static_cast<size_t>(std::stoi(fields[5])),
                static_cast<size_t>(std::stoi(fields[6]))});
        }
    }

    {
        std::ifstream utak("4000C_utak.tsv");
        if(!utak.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

        std::string line;
        for(size_t yin = 0; yin < graph.size(); ++yin) {
            std::getline(utak, line);

            std::stringstream ss(line);
            std::string field;

            size_t yang = 0;
            while(std::getline(ss, field, '\t')) {
                if(field == "0") {
                    ++yang;
                    continue;
                }
                graph[yin].roads.emplace_back(yang++, static_cast<size_t>(std::stoi(field)));
            }
        }
    }

    return graph;
}

void print_next(std::function<void()> f) {
    static size_t counter = 0;
    std::cout << ++counter << ".\n";
    f();
    std::cout << "\n\n";
}
