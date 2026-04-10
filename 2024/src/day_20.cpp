#include "day_20.hpp"
#include <array>
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using i64 = long long;

namespace {
struct Point {
    int r = 0, c = 0;
    bool operator==(const Point &other) const { return r == other.r && c == other.c; }
};
constexpr std::array<std::pair<int, int>, 4> DIRS = {{
    {0, 1},
    {1, 0},
    {-1, 0},
    {0, -1},
}};
template <int MIN_SAVE_TEST, int MAX_CHEAT>
std::string solution(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file" + filepath);
    int MIN_SAVE = filepath.find("test") != std::string::npos ? MIN_SAVE_TEST : 100;
    Point start, end;
    std::string line;
    std::vector<std::string> grid;
    while (std::getline(file, line)) {
        grid.push_back(line);
        if (line.find('S') != std::string::npos) {
            start.r = grid.size() - 1;
            start.c = line.find('S');
        }
        if (line.find('E') != std::string::npos) {
            end.r = grid.size() - 1;
            end.c = line.find('E');
        }
    }
    std::vector<Point> path;
    Point curr = start;
    while (true) {
        path.push_back(curr);
        grid[curr.r][curr.c] = '#';
        if (curr == end) break;
        for (const auto &[dr, dc] : DIRS) {
            Point next = {curr.r + dr, curr.c + dc};
            if (grid[next.r][next.c] != '#') {
                curr = next;
                break;
            }
        }
    }
    i64 valid_cheats = 0;
    // the index for each point in the path is the time it took to reach that point
    for (std::size_t i = 0; i < path.size(); ++i) {
        for (std::size_t j = i + MIN_SAVE; j < path.size(); ++j) {
            // manhattan distance between 2 points is the cheat distance
            int manhattan_dist = std::abs(path[i].r - path[j].r) + std::abs(path[i].c - path[j].c);
            if (manhattan_dist <= MAX_CHEAT) {
                int saved_time = (j - i) - manhattan_dist;
                if (saved_time >= MIN_SAVE) ++valid_cheats;
            }
        }
    }
    return std::to_string(valid_cheats);
}
} // namespace

std::string Day20::part_1(const std::string &filepath) { return solution<2, 2>(filepath); }
std::string Day20::part_2(const std::string &filepath) { return solution<50, 20>(filepath); }