#include "day_11.hpp"
#include <cstdint>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace {
int64_t int_len(int64_t num)
{
    int64_t len = 0;
    for (; num > 0; num /= 10) {
        ++len;
    }
    return len;
}
int64_t pow_10(int64_t exp)
{
    int64_t res = 1;
    while (exp-- > 0) {
        res *= 10;
    }
    return res;
}
template <int BLINK_TIMES>
std::string solution(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::string line;
    std::getline(file, line);
    std::unordered_map<int64_t, int64_t> stone_counts;
    std::istringstream iss{line};
    int64_t stone;
    while (iss >> stone) {
        ++stone_counts[stone];
    }
    for (int blink = 0; blink < BLINK_TIMES; ++blink) {
        std::unordered_map<int64_t, int64_t> new_counts;
        for (const auto &[stone, count] : stone_counts) {
            if (stone == 0) {
                new_counts[1] += count;
            } else {
                int64_t len = int_len(stone);
                if (len % 2 == 0) {
                    int64_t pow10 = pow_10(len / 2);
                    new_counts[stone / pow10] += count;
                    new_counts[stone % pow10] += count;
                } else {
                    new_counts[stone * 2024] += count;
                }
            }
        }
        stone_counts = std::move(new_counts);
    }
    int64_t total = 0;
    for (const auto &[stone, count] : stone_counts) {
        total += count;
    }
    return std::to_string(total);
}
} // namespace

std::string Day11::part_1(const std::string &filepath) { return solution<25>(filepath); }
std::string Day11::part_2(const std::string &filepath) { return solution<75>(filepath); }