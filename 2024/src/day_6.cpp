#include "day_6.hpp"
#include <array>
#include <fstream>
#include <functional>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

const std::array<std::pair<int, int>, 4> DIRS{{
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
}};

struct tuple_hash {
    std::size_t operator()(const std::tuple<int, int, int> &tuple) const
    {
        auto [x, y, dir] = tuple;
        std::size_t hash{};
        hash ^= std::hash<int>{}(x) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= std::hash<int>{}(y) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= std::hash<int>{}(dir) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        return hash;
    }
};

std::vector<std::string> get_map_and_start(const std::string &filepath, int &x, int &y);
bool stop_check(int x, int y, int row, int col);
bool place_obstacle(const std::vector<std::string> &map, int x, int y, int dir);

std::string Day6::part_1(const std::string &filepath)
{
    int x, y;
    auto map = get_map_and_start(filepath, x, y);
    int row = map.size(), col = map[0].size();
    int dir{};
    int visited{1};
    while (true) {
        auto [dx, dy] = DIRS[dir];
        while (map[x][y] != '#') {
            if (map[x][y] == '.') {
                ++visited;
                map[x][y] = 'X';
            }
            x += dx, y += dy;
            if (stop_check(x, y, row, col)) break;
        }
        if (stop_check(x, y, row, col)) break;
        x -= dx, y -= dy;
        dir = (dir + 1) % 4;
    }
    return std::to_string(visited);
}
std::string Day6::part_2(const std::string &filepath)
{
    int x, y;
    auto map = get_map_and_start(filepath, x, y);
    int row = map.size(), col = map[0].size();
    int dir{};
    int obstacles{};
    bool quit{};
    while (!quit) {
        auto [dx, dy] = DIRS[dir];
        while (!(quit = stop_check(x, y, row, col)) && map[x][y] != '#') {
            // Brute-force try placing obstacle on every unvisited node
            if (map[x][y] == '.') {
                map[x][y] = '#';
                if (place_obstacle(map, x - dx, y - dy, dir)) ++obstacles;
                map[x][y] = '-';
            }
            x += dx, y += dy;
        }
        x -= dx, y -= dy;
        dir = (dir + 1) % 4;
    }
    return std::to_string(obstacles);
}
bool place_obstacle(const std::vector<std::string> &map, int x, int y, int dir)
{
    int row = map.size(), col = map[0].size();
    std::unordered_set<std::tuple<int, int, int>, tuple_hash> visited;
    bool quit{};
    while (!quit) {
        auto [dx, dy] = DIRS[dir];
        while (!(quit = stop_check(x, y, row, col)) && map[x][y] != '#') {
            x += dx, y += dy;
        }
        std::tuple<int, int, int> state{x, y, dir};
        if (visited.find(state) != visited.end()) return true;
        visited.insert(state);
        x -= dx, y -= dy;
        dir = (dir + 1) % 4;
    }
    return false;
}
bool stop_check(int x, int y, int row, int col) { return x < 0 || y < 0 || x >= row || y >= col; }
std::vector<std::string> get_map_and_start(const std::string &filepath, int &x, int &y)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::vector<std::string> map;
    std::string line;
    while (std::getline(file, line)) {
        map.push_back(line);
        for (std::size_t i = 0; i < line.size(); ++i) {
            if (line[i] == '^') {
                x = map.size() - 1;
                y = static_cast<int>(i);
            }
        }
    }
    return map;
}