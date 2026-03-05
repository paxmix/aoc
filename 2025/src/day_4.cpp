#include "day_4.hpp"

#include <fstream>
#include <sstream>
#include <vector>

using usize = std::size_t;
using grid = std::vector<std::vector<char>>;
constexpr std::array<std::array<int, 2>, 8> DIRS = {
    {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}};

std::vector<std::vector<char>> to_grid(const std::string &input);
usize neighbors(const grid &diagram, usize i, usize j);

std::string Day4::part_1(std::string filepath)
{
    std::ifstream file(filepath, std::ios::binary);
    std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    grid diagram = to_grid(input);
    usize accessible_rolls = 0;

    for (usize i = 0; i < diagram.size(); ++i) {
        for (usize j = 0; j < diagram[i].size(); ++j) {
            if (diagram[i][j] == '@' && neighbors(diagram, i, j) < 4) {
                ++accessible_rolls;
            }
        }
    }

    return std::to_string(accessible_rolls);
}

std::string Day4::part_2(std::string filepath)
{
    std::ifstream file(filepath, std::ios::binary);
    std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    grid diagram = to_grid(input);
    usize sum = 0;
    while (true) {
        usize accessible_rolls = 0;
        for (usize i = 0; i < diagram.size(); ++i) {
            for (usize j = 0; j < diagram[i].size(); ++j) {
                if (diagram[i][j] == '@' && neighbors(diagram, i, j) < 4) {
                    ++accessible_rolls;
                    diagram[i][j] = 'x';
                }
            }
        }
        if (!accessible_rolls) break;
        sum += accessible_rolls;
    }
    return std::to_string(sum);
}

grid to_grid(const std::string &input)
{
    grid diagram;
    std::istringstream iss(input);
    std::string line;
    while (std::getline(iss, line)) {
        diagram.emplace_back(line.begin(), line.end());
    }
    return diagram;
}

usize neighbors(const grid &diagram, usize i, usize j)
{
    usize count = 0;
    for (const auto &[di, dj] : DIRS) {
        auto ni = i + di;
        auto nj = j + dj;
        if (ni < diagram.size() && nj < diagram[ni].size() && diagram[ni][nj] == '@') {
            ++count;
        }
    }
    return count;
}
