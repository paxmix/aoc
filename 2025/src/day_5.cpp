#include "day_5.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>

using u64 = std::uint64_t;

std::vector<std::pair<u64, u64>> merged_ranges(std::vector<std::pair<u64, u64>> &ranges);
bool in_ranges(const std::vector<std::pair<u64, u64>> &ranges, u64 val);

template <typename Func>
std::string solution(std::string filepath, Func compute_count)
{
    std::ifstream file(filepath);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }

    std::string line;
    std::vector<std::pair<u64, u64>> ranges;
    while (std::getline(file, line) && !line.empty()) {
        size_t pos = line.find('-');
        if (pos == std::string::npos) {
            std::cerr << "Invalid format: " << line << '\n';
        }
        try {
            u64 low = stoull(line.substr(0, pos));
            u64 high = stoull(line.substr(pos + 1));
            ranges.emplace_back(low, high);
        } catch (const std::exception &e) {
            std::cerr << "Parsing error in\"" << line << "\":" << e.what() << '\n';
            continue;
        }
    }

    std::sort(ranges.begin(), ranges.end());
    ranges = merged_ranges(ranges);
    return compute_count(ranges, file);
}

std::string Day5::part_1(std::string filepath)
{
    return solution(filepath, [](const auto &ranges, std::ifstream &file) {
        size_t count = 0;
        std::string line;
        while (std::getline(file, line)) {
            try {
                u64 val = stoull(line);
                if (in_ranges(ranges, val)) {
                    ++count;
                }
            } catch (const std::exception &e) {
                std::cerr << "Parsing error in\"" << line << "\":" << e.what() << '\n';
                continue;
            }
        }

        return std::to_string(count);
    });
}

std::string Day5::part_2(std::string filepath)
{
    return solution(filepath, [](const auto &ranges, std::ifstream &) {
        size_t count = 0;
        for (const auto &range : ranges) {
            count += range.second - range.first + 1;
        }
        return std::to_string(count);
    });
}

std::vector<std::pair<u64, u64>> merged_ranges(std::vector<std::pair<u64, u64>> &ranges)
{
    std::vector<std::pair<u64, u64>> merged;
    for (auto range : ranges) {
        if (merged.empty() || range.first > merged.back().second + 1) {
            merged.push_back(range);
        } else if (range.second > merged.back().second) {
            merged.back().second = range.second;
        }
    }

    return merged;
}

bool in_ranges(const std::vector<std::pair<u64, u64>> &ranges, u64 val)
{
    auto it = std::upper_bound(ranges.begin(), ranges.end(), val, [](u64 value, const auto &range) {
        return value <= range.first;
    });

    if (it == ranges.begin()) {
        return false;
    }
    --it;
    return val <= it->second;
}
