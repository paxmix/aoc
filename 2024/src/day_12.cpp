#include "day_12.hpp"
#include <array>
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
struct Direction {
    int dx, dy;
};
constexpr std::array<Direction, 8> DIRS = {{
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
    {0, -1},
    {-1, -1},
}};

struct Point {
    int x, y;
};
int get_corners(const std::vector<std::string> &grid, const Point &curr, int rows, int cols, char plant_type)
{
    int corners = 0;
    for (int i = 0; i < 8; i += 2) {
        int x1 = curr.x + DIRS[i].dx; // Cardinal 1
        int y1 = curr.y + DIRS[i].dy;
        int x2 = curr.x + DIRS[(i + 2) % 8].dx; // Cardinal 2
        int y2 = curr.y + DIRS[(i + 2) % 8].dy;
        int xd = curr.x + DIRS[(i + 1) % 8].dx; // Diagonal between them
        int yd = curr.y + DIRS[(i + 1) % 8].dy;
        bool n1 = x1 >= 0 && y1 >= 0 && x1 < rows && y1 < cols && grid[x1][y1] == plant_type;
        bool n2 = x2 >= 0 && y2 >= 0 && x2 < rows && y2 < cols && grid[x2][y2] == plant_type;
        bool nd = xd >= 0 && yd >= 0 && xd < rows && yd < cols && grid[xd][yd] == plant_type;
        if (!n1 && !n2) ++corners;      // Outer corner
        if (n1 && n2 && !nd) ++corners; // Inner corner (concave)
    }
    return corners;
}
template <bool COUNT_CORNERS>
std::string solution(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::vector<std::string> grid;
    std::string line;
    while (std::getline(file, line)) {
        grid.push_back(line);
    }
    int rows = grid.size();
    int cols = grid[0].size();
    int64_t total_price = 0;
    std::vector<bool> visited(rows * cols, false);
    std::vector<Point> vstack;
    vstack.reserve(rows * cols);
    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < cols; ++y) {
            vstack.clear();
            if (visited[x * cols + y]) continue;
            // New Region Found
            char plant_type = grid[x][y];
            int64_t area = 0;
            int64_t total_sides = 0;
            int64_t perimeter = 0;
            vstack.emplace_back(x, y);
            visited[x * cols + y] = true;
            while (!vstack.empty()) {
                Point curr = vstack.back();
                vstack.pop_back();
                ++area;
                if constexpr (COUNT_CORNERS) total_sides += get_corners(grid, curr, rows, cols, plant_type);
                for (int i = 0; i < 8; i += 2) {
                    int nx = curr.x + DIRS[i].dx;
                    int ny = curr.y + DIRS[i].dy;
                    // Check bounds
                    if (nx >= 0 && ny >= 0 && nx < rows && ny < cols) {
                        if (grid[nx][ny] == plant_type) {
                            if (!visited[nx * cols + ny]) {
                                visited[nx * cols + ny] = true;
                                vstack.emplace_back(nx, ny);
                            }
                        } else if constexpr (!COUNT_CORNERS) {
                            // Different plant type means a fence is needed
                            ++perimeter;
                        }
                    } else if constexpr (!COUNT_CORNERS) {
                        // Out of bounds means a fence is needed
                        ++perimeter;
                    }
                }
            }
            if constexpr (COUNT_CORNERS) {
                total_price += area * total_sides;
            } else {
                total_price += area * perimeter;
            }
        }
    }
    return std::to_string(total_price);
}
} // namespace

std::string Day12::part_1(const std::string &filepath) { return solution<false>(filepath); }
std::string Day12::part_2(const std::string &filepath) { return solution<true>(filepath); }