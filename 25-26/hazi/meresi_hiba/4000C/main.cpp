#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "megoldasok.hpp"
#include "struct.hpp"

settlement_graph parse();

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    settlement_graph graph = parse();

    // 1.
    std::cout << "1.\n";
    // print_graphviz(graph);
    std::cout << "\n\n";

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
