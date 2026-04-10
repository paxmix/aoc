#include "day_10.hpp"
#include <array>
#include <fstream>
#include <queue>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace {
constexpr std::array<std::pair<int, int>, 4> DIRS = {{
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
}};
enum class Algor { BFS, DFS };
bool is_valid(int x, int y, int row, int col) { return x >= 0 && y >= 0 && x < row && y < col; }
int bfs(int x0, int y0, const std::vector<std::vector<int>> &map)
{
    int row = map.size();
    int col = map[0].size();
    std::set<std::pair<int, int>> visited_peaks;
    std::queue<std::pair<int, int>> q;
    q.emplace(x0, y0);
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (map[x][y] == 9) {
            visited_peaks.insert({x, y});
            continue;
        }
        for (const auto &[dx, dy] : DIRS) {
            int nx = x + dx;
            int ny = y + dy;
            if (is_valid(nx, ny, row, col) && map[nx][ny] == map[x][y] + 1) {
                q.emplace(nx, ny);
            }
        }
    }
    return visited_peaks.size();
}
int dfs(int x, int y, int next, const std::vector<std::vector<int>> &map)
{
    if (map[x][y] == 9) return 1;
    int count = 0;
    for (const auto &[dx, dy] : DIRS) {
        int nx = x + dx;
        int ny = y + dy;
        if (is_valid(nx, ny, map.size(), map[0].size()) && map[nx][ny] == next) {
            count += dfs(nx, ny, next + 1, map);
        }
    }
    return count;
}
template <Algor algorithm>
std::string solution(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::vector<std::pair<int, int>> trailheads;
    std::vector<std::vector<int>> map;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> nums;
        for (int col = 0; col < static_cast<int>(line.length()); ++col) {
            if (line[col] == '0') trailheads.emplace_back(map.size(), col);
            nums.push_back(line[col] - '0');
        }
        map.push_back(nums);
    }
    int total = 0;
    for (const auto &[x, y] : trailheads) {
        if constexpr (algorithm == Algor::BFS) {
            total += bfs(x, y, map);
        } else if constexpr (algorithm == Algor::DFS) {
            total += dfs(x, y, 1, map);
        }
    }
    return std::to_string(total);
}
} // namespace

std::string Day10::part_1(const std::string &filepath) { return solution<Algor::BFS>(filepath); }
std::string Day10::part_2(const std::string &filepath) { return solution<Algor::DFS>(filepath); }