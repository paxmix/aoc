#include "day_13.hpp"
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>

namespace {
using i64 = long long;
template <bool PRIZE_INCREASE>
std::string solution(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file");
    std::string line;
    i64 tokens = 0;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        i64 ax, ay, bx, by, px, py;
        if (std::sscanf(line.c_str(), "Button A: X+%lld, Y+%lld", &ax, &ay) == 2) {
            std::getline(file, line);
            std::sscanf(line.c_str(), "Button B: X+%lld, Y+%lld", &bx, &by);
            std::getline(file, line);
            std::sscanf(line.c_str(), "Prize: X=%lld, Y=%lld", &px, &py);
            if constexpr (PRIZE_INCREASE) {
                px += 10'000'000'000'000;
                py += 10'000'000'000'000;
            }
            i64 det = ax * by - ay * bx;
            i64 top_a = px * by - py * bx;
            i64 top_b = ax * py - ay * px;
            if (det != 0 && top_a % det == 0 && top_b % det == 0) {
                i64 a_count = top_a / det;
                i64 b_count = top_b / det;
                if (a_count >= 0 && b_count >= 0) tokens += a_count * 3 + b_count;
            }
        }
    }
    return std::to_string(tokens);
}
} // namespace

std::string Day13::part_1(const std::string &filepath) { return solution<false>(filepath); }
std::string Day13::part_2(const std::string &filepath) { return solution<true>(filepath); }