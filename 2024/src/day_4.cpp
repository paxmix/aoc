#include "day_4.hpp"
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

const std::array<std::pair<int, int>, 8> DIRS{{
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, -1},
    {0, 1},
    {1, -1},
    {1, 0},
    {1, 1},
}};

std::vector<std::string> get_grid(const std::string &filepath);
int xmas_count(const std::vector<std::string> &grids, int x, int y, int row, int col);
bool is_x_mas(const std::vector<std::string> &grids, int i, int j);

std::string Day4::part_1(const std::string &filepath)
{
    std::vector<std::string> grids = get_grid(filepath);
    int count{};
    int row = static_cast<int>(grids.size());
    int col = static_cast<int>(grids[0].size());
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (grids[i][j] == 'X') {
                count += xmas_count(grids, i, j, row, col);
            }
        }
    }
    return std::to_string(count);
}
std::string Day4::part_2(const std::string &filepath)
{
    std::vector<std::string> grids = get_grid(filepath);
    int count{};
    for (int i = 1; i < static_cast<int>(grids.size()) - 1; ++i) {
        for (int j = 1; j < static_cast<int>(grids[0].size()) - 1; ++j) {
            if (grids[i][j] == 'A' && is_x_mas(grids, i, j)) {
                ++count;
            }
        }
    }
    return std::to_string(count);
}
int xmas_count(const std::vector<std::string> &grids, int x, int y, int row, int col)
{
    int count{};
    for (const auto &[dx, dy] : DIRS) {
        if (x + 3 * dx < 0 || x + 3 * dx >= row) continue;
        if (y + 3 * dy < 0 || y + 3 * dy >= col) continue;
        if (grids[x + dx][y + dy] == 'M' && grids[x + 2 * dx][y + 2 * dy] == 'A' &&
            grids[x + 3 * dx][y + 3 * dy] == 'S') {
            ++count;
        }
    }
    return count;
}
bool is_x_mas(const std::vector<std::string> &grids, int i, int j)
{
    auto is_pair = [](char a, char b) { return (a == 'M' && b == 'S') || (a == 'S' && b == 'M'); };
    char t_l = grids[i - 1][j - 1];
    char t_r = grids[i - 1][j + 1];
    char b_l = grids[i + 1][j - 1];
    char b_r = grids[i + 1][j + 1];
    return is_pair(t_l, b_r) && is_pair(t_r, b_l);
}
std::vector<std::string> get_grid(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::vector<std::string> grids;
    std::string line;
    while (std::getline(file, line)) {
        grids.push_back(line);
    }
    return grids;
}