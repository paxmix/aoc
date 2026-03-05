#include "day_3.hpp"
#include <cstdint>
#include <fstream>
#include <iostream>

using u64 = std::uint64_t;
using usize = std::size_t;

template <usize length>
std::string solution(std::string filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return "";
    }

    u64 sum = 0;
    std::string bank;
    std::array<char, length> max_joltage;
    while (std::getline(file, bank)) {
        usize top = 0;
        usize bank_len = bank.size();
        for (usize i = 0; i < bank_len; ++i) {
            char battery = bank[i];
            usize remaining = bank_len - i;

            while (top != 0 && max_joltage[top - 1] < battery && top + remaining > length) {
                --top;
            }
            if (top < length) {
                max_joltage[top++] = battery;
            }
        }
        u64 val = 0;
        for (usize i = 0; i < length; ++i) {
            val = val * 10 + static_cast<u64>(max_joltage[i] - '0');
        }
        sum += val;
    }
    return std::to_string(sum);
}

std::string Day3::part_1(std::string filepath)
{
    return solution<2>(filepath);
}

std::string Day3::part_2(std::string filepath)
{
    return solution<12>(filepath);
}
