#include "day_16.hpp"
#include <algorithm>
#include <array>
#include <fstream>
#include <queue>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
struct State {
    int x, y, dir, score;
    // Overload for min-heap priority queue
    bool operator>(const State &other) const { return score > other.score; }
};

constexpr std::array<std::pair<int, int>, 4> DIRS = {{
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1},
}};
constexpr int BIG_NUM = 1'000'000'000;

template <bool BEST_SITS>
std::string solution(const std::string &filepath)
{

    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::vector<std::string> grid;
    std::string line;
    int sx = 0, sy = 0, ex = 0, ey = 0;
    while (std::getline(file, line)) {
        grid.push_back(line);
        if (line.find('S') != std::string::npos) {
            sx = line.find('S');
            sy = grid.size() - 1;
        }
        if (line.find('E') != std::string::npos) {
            ex = line.find('E');
            ey = grid.size() - 1;
        }
    }
    int rows = grid.size();
    int cols = grid[0].size();

    // dist[x][y][dir], initialized to int_max, function as a map
    std::vector<int> dist(rows * cols * 4, BIG_NUM);
    auto dist_idx = [&](int x, int y, int d) { return (x * cols + y) * 4 + d; };
    std::vector<std::pair<int, std::pair<int, int>>> parents[150][150][4];
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    pq.emplace(sx, sy, 0, 0);
    dist[dist_idx(sx, sy, 0)] = 0;

    int min_total_score = BIG_NUM;

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();
        if (curr.score > dist[dist_idx(curr.x, curr.y, curr.dir)]) continue;
        if (grid[curr.y][curr.x] == 'E') min_total_score = std::min(min_total_score, curr.score);

        // Try 3 actions: Forward, Turn L, Turn R
        auto [dx, dy] = DIRS[curr.dir];
        std::array<State, 3> next_states = {{
            {curr.x + dx, curr.y + dy, curr.dir, curr.score + 1},
            {curr.x, curr.y, (curr.dir + 1) % 4, curr.score + 1000},
            {curr.x, curr.y, (curr.dir + 3) % 4, curr.score + 1000},
        }};

        for (auto &n : next_states) {
            if (grid[n.y][n.x] == '#') continue;
            if (n.score < dist[dist_idx(n.x, n.y, n.dir)]) {
                dist[dist_idx(n.x, n.y, n.dir)] = n.score;
                if constexpr (BEST_SITS) parents[n.x][n.y][n.dir] = {{curr.dir, {curr.x, curr.y}}};
                pq.push(n);
            } else if constexpr (BEST_SITS) {
                if (n.score == dist[dist_idx(n.x, n.y, n.dir)]) {
                    parents[n.x][n.y][n.dir].push_back({curr.dir, {curr.x, curr.y}});
                }
            }
        }
    }

    if constexpr (!BEST_SITS) {
        return std::to_string(min_total_score);
    }
    //  Backtrack
    std::set<std::pair<int, int>> best_tiles;
    std::queue<std::pair<int, std::pair<int, int>>> bq; // {dir, {x, y}}

    for (int d = 0; d < 4; d++) {
        if (dist[dist_idx(ex, ey, d)] == min_total_score) bq.push({d, {ex, ey}});
    }

    std::set<std::pair<int, std::pair<int, int>>> visited_states;
    while (!bq.empty()) {
        auto curr = bq.front();
        bq.pop();
        if (visited_states.count(curr)) continue;
        visited_states.insert(curr);

        best_tiles.insert(curr.second);
        for (auto &p : parents[curr.second.first][curr.second.second][curr.first]) {
            bq.push(p);
        }
    }
    if constexpr (BEST_SITS) {
        return std::to_string(best_tiles.size());
    }
}
} // namespace

std::string Day16::part_1(const std::string &filepath) { return solution<false>(filepath); }
std::string Day16::part_2(const std::string &filepath) { return solution<true>(filepath); }