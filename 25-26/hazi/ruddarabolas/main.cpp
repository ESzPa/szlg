#include <iostream>
#include <queue>

std::pair<int, int> darabol(std::priority_queue<int, std::vector<int>, std::greater<int>>& pq) {
    int first = pq.top();
    pq.pop();
    int second = pq.top();
    pq.pop();
    pq.push(first + second);
    return {first + second, first};
}

int main(void) {
    int N;
    std::cin >> N;

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    std::vector<std::pair<int, int>> log;

    for(int i = 0; i < N; ++i) {
        int _;
        std::cin >> _;
        pq.push(_);
    }

    size_t cost = 0;
    while(pq.size() > 1) {
        log.push_back(darabol(pq));
        cost += log.back().first;
    }

    std::cout << cost << '\n';

    for(auto i = log.rbegin(); i != log.rend(); ++i) {
        std::cout << i->first << ' ' << i->second << '\n';
    }

    return 0;
}
