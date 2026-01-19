#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include "struct.hpp"

netgraph parse() {
    netgraph graph;

    {
        std::ifstream tanulok("4000B_tanulok.tsv");
        if(!tanulok.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

        std::string line;
        while(std::getline(tanulok, line)) {
            std::vector<std::string> fields;
            std::stringstream ss(line);
            std::string field;

            while(std::getline(ss, field, '\t')) {
                fields.push_back(field);
            }

            Matcsop matcsop = (fields[2] == "alfa" ? Matcsop::alfa : Matcsop::beta);
            Ancsop ancsop = static_cast<Ancsop>(std::stoi(std::to_string(fields[3][0])));
            Lang nyelv2 = (fields[3] == "német" ? Lang::nemet : Lang::nemet);
            bool nem = fields[4] == "F";
            int egyuttlakok = std::stoi(fields[5]);
            int testverek = std::stoi(fields[6]);

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
                if(fields[i] == "1") {
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

    return 0;
}
