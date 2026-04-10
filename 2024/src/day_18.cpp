#include "day_18.hpp"
#include <array>
#include <cstdio>
#include <format>
#include <fstream>
#include <queue>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace {
constexpr std::array<std::pair<int, int>, 4> DIRS = {{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
}};
struct Node {
    int x, y, dist;
    bool operator>(const Node &other) const { return dist > other.dist; }
};
struct Byte {
    int x, y;
};
constexpr int BIG_NUM = 1'000'000'000;
bool is_valid(int x, int y, int rows, int cols) { return x >= 0 && y >= 0 && x < cols && y < rows; }
bool possible(int x, int y, int grid_size, std::vector<bool> &visited, const std::vector<std::string> &grid)
{
    if (x == grid_size - 1 && y == grid_size - 1) return true;
    visited[y * grid_size + x] = true;
    for (const auto &[dx, dy] : DIRS) {
        int nx = x + dx;
        int ny = y + dy;
        if (is_valid(nx, ny, grid_size, grid_size) && grid[ny][nx] == '.' && !visited[ny * grid_size + nx]) {
            if (possible(nx, ny, grid_size, visited, grid)) return true;
        }
    }
    return false;
}
} // namespace

std::string Day18::part_1(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    int BYTES_FALL;
    int GRIDS_SIZE;
    if (filepath.find("test") != std::string::npos) {
        GRIDS_SIZE = 7;
        BYTES_FALL = 12;
    } else {
        GRIDS_SIZE = 71;
        BYTES_FALL = 1024;
    }
    std::vector<std::string> grid(GRIDS_SIZE, std::string(GRIDS_SIZE, '.'));
    std::string line;
    for (int b = 0; b < BYTES_FALL; ++b) {
        std::getline(file, line);
        int x, y;
        std::sscanf(line.c_str(), "%d,%d", &x, &y);
        grid[y][x] = '#';
    }
    // min-heap priority queue
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    std::vector<int> min_dist(GRIDS_SIZE * GRIDS_SIZE, BIG_NUM);
    pq.emplace(0, 0, 0);
    min_dist[0] = 0;
    while (!pq.empty()) {
        auto [x, y, dist] = pq.top();
        pq.pop();
        if (dist > min_dist[y * GRIDS_SIZE + x]) continue;
        if (x == GRIDS_SIZE - 1 && y == GRIDS_SIZE - 1) return std::to_string(dist);
        for (const auto &[dx, dy] : DIRS) {
            int nx = x + dx;
            int ny = y + dy;
            if (is_valid(nx, ny, GRIDS_SIZE, GRIDS_SIZE) && grid[nx][ny] != '#') {
                if (min_dist[y * GRIDS_SIZE + x] + 1 < min_dist[ny * GRIDS_SIZE + nx]) {
                    min_dist[ny * GRIDS_SIZE + nx] = min_dist[y * GRIDS_SIZE + x] + 1;
                    pq.emplace(nx, ny, min_dist[ny * GRIDS_SIZE + nx]);
                }
            }
        }
    }
    return std::to_string(-1);
}
std::string Day18::part_2(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    int BYTES_FALL;
    int GRIDS_SIZE;
    if (filepath.find("test") != std::string::npos) {
        GRIDS_SIZE = 7;
        BYTES_FALL = 12;
    } else {
        GRIDS_SIZE = 71;
        BYTES_FALL = 1024;
    }
    std::string line;
    std::vector<Byte> all_bytes;
    while (std::getline(file, line)) {
        int x, y;
        std::sscanf(line.c_str(), "%d,%d", &x, &y);
        all_bytes.emplace_back(x, y);
    }
    int low = BYTES_FALL;
    int high = all_bytes.size() - 1;
    int result = -1;
    while (low <= high) {
        std::vector<std::string> grid(GRIDS_SIZE, std::string(GRIDS_SIZE, '.'));
        int mid = low + (high - low) / 2;
        for (int i = 0; i <= mid; ++i) {
            auto [xi, yi] = all_bytes[i];
            grid[yi][xi] = '#';
        }
        std::vector<bool> visited(GRIDS_SIZE * GRIDS_SIZE, false);
        if (!possible(0, 0, GRIDS_SIZE, visited, grid)) {
            high = mid - 1;
            result = mid;
        } else {
            low = mid + 1;
        }
    }
    if (result != -1) return std::format("{},{}", all_bytes[result].x, all_bytes[result].y);
    return "impossible";
}