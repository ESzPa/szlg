#include <iostream>
#include <queue>
#include <vector>

struct Position {
    int x, y;
    constexpr Position& operator+=(const Position& other) noexcept {
        x += other.x;
        y += other.y;
        return *this;
    }
    constexpr Position operator+(const Position& other) const noexcept {
        return {x + other.x, y + other.y};
    }
};

constexpr Position dirs[] = {Position{-1, -1}, Position{-1, 0}, Position{-1, 1}, Position{0, -1},
                             Position{0, 1},   Position{1, -1}, Position{1, 0},  Position{1, 1}};

std::vector<std::vector<bool>> read();
void update_explored(const std::vector<std::vector<bool>>& bmap, Position start,
                     std::vector<std::vector<bool>>& explored_map);

int main(void) {
    auto bmap = read();
    size_t width = bmap[0].size();
    std::vector<std::vector<bool>> explored_map(bmap.size(), std::vector<bool>(width, 0));

    size_t count = 0;
    for(size_t i = 0; i < bmap.size() * width; ++i) {
        size_t y = i / width;
        size_t x = i % width;

        if(bmap[y][x] && !explored_map[y][x]) {
            ++count;
            update_explored(bmap, {(int)x, (int)y}, explored_map);
        }
    }

    std::cout << count << '\n';

    return 0;
}

std::vector<std::vector<bool>> read() {
    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<bool>> bmap(N, std::vector<bool>(M, false));
    for(int i = 0; i < N; ++i) {
        std::string line;
        std::cin >> line;
        for(int j = 0; j < M; ++j) {
            bmap[i][j] = (line[j] == 'Z');
        }
    }

    return bmap;
}

template <typename T>
inline bool out_of_bounds(const std::vector<std::vector<T>>& matrix, Position pos) noexcept {
    const auto rows = matrix.size();
    const auto cols = rows ? matrix.front().size() : 0;
    return static_cast<size_t>(pos.y) >= rows || static_cast<size_t>(pos.x) >= cols;
}

void update_explored(const std::vector<std::vector<bool>>& bmap, Position start,
                     std::vector<std::vector<bool>>& explored_map) {
    std::queue<Position> q;
    q.push(start);
    explored_map[start.y][start.x] = true;

    while(!q.empty()) {
        Position cur = q.front();
        q.pop();

        for(auto dir : dirs) {
            Position neighbour = cur + dir;
            if(!out_of_bounds(bmap, neighbour) && bmap[neighbour.y][neighbour.x] &&
               !explored_map[neighbour.y][neighbour.x]) {
                q.push(neighbour);
                explored_map[neighbour.y][neighbour.x] = true;
            }
        }
    }
}
