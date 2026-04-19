#include "day_14.hpp"
#include <array>
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
class Robot {
  public:
    Robot(int x, int y, int vx, int vy) : x0_(x), y0_(y), vx_(vx), vy_(vy) {}
    std::pair<int, int> get_pos(int t, int row, int col) const
    {
        long long nx = x0_ + static_cast<long long>(vx_) * t;
        long long ny = y0_ + static_cast<long long>(vy_) * t;
        nx = (nx % col + col) % col;
        ny = (ny % row + row) % row;
        return {nx, ny};
    }

  private:
    int x0_, y0_, vx_, vy_;
};
} // namespace

std::string Day14::part_1(const std::string &filepath)
{
    if (filepath.find("test") != std::string::npos) {
        col_ = 7;
        row_ = 11;
    } else {
        col_ = 101;
        row_ = 103;
    }
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::string line;
    std::array<int, 4> quadrants{};
    int mid_col = col_ / 2;
    int mid_row = row_ / 2;
    while (std::getline(file, line)) {
        int x, y, vx, vy;
        if (std::sscanf(line.c_str(), "p=%d,%d v=%d,%d", &x, &y, &vx, &vy) == 4) {
            auto [nx, ny] = Robot{x, y, vx, vy}.get_pos(100, row_, col_);
            if (nx == mid_col || ny == mid_row) continue;
            int idx = (nx < mid_col ? 0 : 2) + (ny < mid_row ? 0 : 1);
            ++quadrants[idx];
        }
    }
    return std::to_string(quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3]);
}
std::string Day14::part_2(const std::string &filepath)
{
    if (filepath.find("test") != std::string::npos) {
        col_ = 7;
        row_ = 11;
    } else {
        col_ = 101;
        row_ = 103;
    }
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::vector<Robot> robots;
    std::string line;
    while (std::getline(file, line)) {
        int x, y, vx, vy;
        if (std::sscanf(line.c_str(), "p=%d,%d v=%d,%d", &x, &y, &vx, &vy) == 4) {
            robots.emplace_back(x, y, vx, vy);
        }
    }
    for (int t = 1; t < col_ * row_; ++t) {
        std::vector<std::string> grid(row_, std::string(col_, ' '));
        for (const auto &robot : robots) {
            auto [nx, ny] = robot.get_pos(t, row_, col_);
            grid[ny][nx] = '#';
        }
        for (const auto &row : grid) {
            // find a long line
            if (row.find(std::string(10, '#')) != std::string::npos) return std::to_string(t);
        }
    }
    return "Tree not found";
}
