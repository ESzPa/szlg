#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>

#include "megoldasok.hpp"
#include "struct.hpp"

netgraph parse() {
    netgraph graph;

    {
        std::ifstream tanulok("4000B_tanulok.tsv");
        if(!tanulok.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

        std::string line;
        std::getline(tanulok, line);
        while(std::getline(tanulok, line)) {
            std::vector<std::string> fields;
            std::stringstream ss(line);
            std::string field;

            while(std::getline(ss, field, '\t')) {
                fields.push_back(field);
            }

            Matcsop matcsop = (fields[2] == "alfa" ? Matcsop::alfa : Matcsop::beta);
            Ancsop ancsop = static_cast<Ancsop>(fields[3][0] - '0');
            Lang nyelv2 = (fields[4] == "német" ? Lang::nemet : Lang::spanyol);
            bool nem = fields[5] == "F";
            int egyuttlakok = std::stoi(fields[6]);
            int testverek = std::stoi(fields[7]);

            graph.emplace_back(
                pupil{fields[1], matcsop, ancsop, nyelv2, nem, egyuttlakok, testverek, {}});
        }
    }

    {
        std::ifstream kapcsolatok("4000B_kapcsolatok.tsv");
        if(!kapcsolatok.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

        std::string line;
        int i = 0;
        while(std::getline(kapcsolatok, line)) {
            std::vector<std::string> fields;
            std::stringstream ss(line);
            std::string field;

            while(std::getline(ss, field, '\t')) {
                fields.push_back(field);
            }

            for(int j = 0; j < 36; ++j) { // Number of students
                if(fields[j] == "1") {
                    graph[i].buddies.push_back(j);
                }
            }
            std::sort(graph[i].buddies.begin(), graph[i].buddies.end());

            ++i;
        }
    }

    return graph;
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    netgraph graph = parse();

    // 1.
    std::cout << "1.\n";
    // print_graphviz(graph);
    std::cout << '\n';

    // 2.
    std::cout << "2.\n" << std::boolalpha << are_buddies(graph, "Vagd Alma", "Parady Csoma") << "\n\n";

    // 3.
    std::cout << "3.\n" << std::boolalpha << are_buddies(graph, "Vagd Alma", "Ordy Bálint") << "\n\n";

    // 4.

    // 5.
    std::cout << "5.\n" << buddy_count(graph, "Ordy Bálint") << "\n\n";

    // 6.
    std::cout << "6.\n" << buddy_count(graph, "Mérta Nóra") << "\n\n";

    // 7.
    std::cout << "7.\n" << buddy_count_cmp(graph, [](size_t a, size_t b) { return a > b; }) << "\n\n";

    // 8.
    std::cout << "8.\n" << buddy_count_cmp(graph, [](size_t a, size_t b) { return a < b; }) << "\n\n";

    // 9.
    std::cout << "9.\n"
              << std::boolalpha
              << (buddy_count_with_property(
                      graph, "Ne Pál",
                      [](const netgraph& g, size_t idx) { return g[idx].matcsop == Matcsop::beta; }) > 0)
              << "\n\n";

    // 10.
    std::cout << "10.\n"
              << buddy_count_with_property(
                     graph, "Ne Pál", [](const netgraph& g, size_t idx) { return g[idx].testverek > 1; })
              << "\n\n";

    // 11.
    std::cout << "11.\n";
    for(auto p : buddies_of(graph, "Lapos Elemér")) {
        std::cout << p.name << "; ";
    }
    std::cout << "\n\n";

    // 12.
    {
        size_t count = 0;
        auto it = std::find_if(graph.begin(), graph.end(),
                               [](const pupil& p) { return p.name == "Meg Gyõzõ"; });
        count += it->buddies.size();
        for(auto p : it->buddies) {
            count += graph[p].testverek;
        }
        std::cout << "12.\n" << count << "\n\n";
    }

    // 13.
    std::cout << "13.\n" << indirect_buddies(graph, "Szüre Tibor").size() << "\n\n";

    // 14.
    {
        auto it = std::find_if(graph.begin(), graph.end(),
                               [](const pupil& p) { return p.name == "Hot Elek"; });
        std::set<size_t> idxs;
        for(auto yin : it->buddies) {
            idxs.insert(yin);
            for(auto yang : graph[yin].buddies) {
                idxs.insert(yang);
            }
        }
        std::cout << "14.\n" << idxs.size() << "\n\n";
    }

    // 15.
    {
        auto km = std::find_if(graph.begin(), graph.end(),
                               [](const pupil& p) { return p.name == "Kor Mihály"; });
        auto cd = std::find_if(graph.begin(), graph.end(),
                               [](const pupil& p) { return p.name == "Citad Ella"; });

        std::vector<bool> visited(graph.size(), false);
        std::vector<int> path;
        if(indirect_path_search(graph, (int)(km - graph.begin()), (int)(cd - graph.begin()), visited,
                                path)) {
            std::cout << "15.\n";
            for(auto e : path) {
                std::cout << graph[e].name << " -> ";
            }
            std::cout << "\n\n";
        }
    }

    // 16.
    {
        std::vector<int> res = all_reachable_if(
            graph, "Feles Elek", [&graph](int t, int c) { return graph[t].nyelv2 == graph[c].nyelv2; });
        std::vector<int> all;
        auto it = std::find_if(graph.begin(), graph.end(),
                               [](const pupil& p) { return p.name == "Feles Elek"; });
        for(int i = 0; i < graph.size(); ++i) {
            if(graph[i].nyelv2 == it->nyelv2) {
                all.push_back(i);
            }
        }

        std::cout << "16.\n" << (all.size() == res.size() ? "Igen" : "Nem") << "\n\n";
    }

    return 0;
}
