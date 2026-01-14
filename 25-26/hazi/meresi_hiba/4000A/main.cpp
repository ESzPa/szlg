#include <fstream>
#include <sstream>
#include <string>

#include "megoldasok.hpp"

FaGraph parse();

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    FaGraph graph = parse();

    // 1.
    std::cout << "1.\n";
    // print_graphviz(graph);
    std::cout << "Commented\n";
    std::cout << '\n';

    // 2.
    std::cout << "2.\n" << std::boolalpha << are_connected(graph, 601, 672) << "\n\n";

    // 3.
    std::cout << "3.\n" << std::boolalpha << are_connected(graph, 601, 666) << "\n\n";

    // 4.
    std::cout << "4.\n" << low_node(graph) << "\n\n";

    // 5.
    std::cout << "5.\n" << high_node(graph) << "\n\n";

    // 6.
    int six = most_popular_node(graph);
    std::cout << "6.\n" << six << '\n';
    for(int con : graph[six].connected) {
        std::cout << con << "; ";
    }
    std::cout << "\n\n";

    // 7.
    auto seven = steepest_con(graph);
    std::cout << "7.\n" << seven.first << " -> " << seven.second << "\n\n";

    // 8.
    std::cout << "8.\n" << std::boolalpha << is_reachable(graph, 628, 676) << "\n\n";

    // 9.
    std::cout << "9.\n" << std::boolalpha << is_reachable(graph, 695, 698) << "\n\n";

    // 10.
    std::cout << "10.\n"
              << all_reachable(graph, 686, [](FaNode a, FaNode b) { return a.height > b.height; }).size()
              << "\n\n";

    // 11.
    std::cout
        << "11.\n"
        << all_reachable(graph, 686, [](FaNode a, FaNode b) { return b.type == FATYPE::TOLGY; }).size()
        << "\n\n";

    // 12.
    std::cout
        << "12.\n"
        << all_reachable(graph, 686, [](FaNode a, FaNode b) { return b.type == FATYPE::JUHAR; }).size()
        << "\n\n";

    // 13.
    std::cout << "13.\n"
              << std::boolalpha
              << (all_reachable(graph, 686, [](FaNode a, FaNode b) { return b.type == FATYPE::KORIS; })
                      .size() > 0)
              << "\n\n";

    // 14.
    std::cout << "14.\n"
              << std::boolalpha
              << (all_reachable(graph, 686,
                                [](FaNode a, FaNode b) { return b.type == FATYPE::VADGESZTENYE; })
                      .size() > 0)
              << "\n\n";

    // 15.
    std::cout << "15.\n" << longest_run(graph, 686) << "\n\n";

    // 16.
    std::cout << "16.\n" << steepest_from(graph, 686) << "\n\n";

    // 17.
    std::cout << "17.\n";
    for(int id : collect_all_type(graph, 686, FATYPE::BUKK)) {
        std::cout << id << "; ";
    }
    std::cout << "\n\n";

    // 18.
    std::cout << "18.\n";
    for(int id : collect_all_type(graph, 686, FATYPE::KORIS)) {
        std::cout << id << "; ";
    }
    std::cout << "\n\n";

    // 19.
    std::cout << "20.\n" << shortest_path(graph, 65, 698).size() << "\n\n";

    // 20.
    std::cout << "20.\n";
    for(int id : shortest_path(graph, 695, 698)) {
        std::cout << id << " -> ";
    }
    std::cout << "\n\n";

    return 0;
}

FaGraph parse() {
    FaGraph graph;

    std::string line;

    {
        std::ifstream fakf("4000A_fak.tsv");
        if(!fakf) {
            throw std::runtime_error("File not found");
        }

        std::getline(fakf, line);
        while(std::getline(fakf, line)) {
            std::vector<std::string> fields;
            std::stringstream ss(line);
            std::string field;

            while(std::getline(ss, field, '\t')) {
                fields.push_back(field);
            }

            graph[std::stoi(fields[0])] = {.height = std::stoi(fields[1]),
                                           .type = str_to_fatype(fields[2])};
        }
    }

    {
        std::ifstream kotelekf("4000A_kotelek.tsv");
        if(!kotelekf) {
            throw std::runtime_error("File not found");
        }

        std::getline(kotelekf, line);
        while(std::getline(kotelekf, line)) {
            std::vector<std::string> fields;
            std::stringstream ss(line);
            std::string field;

            while(std::getline(ss, field, '\t')) {
                fields.push_back(field);
            }

            graph[std::stoi(fields[0])].connected.push_back(std::stoi(fields[1]));
        }
    }

    return graph;
}
