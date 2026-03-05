#include "day_7.hpp"
#include <fstream>
#include <ranges>
#include <sstream>
#include <vector>

std::string Day7::part_1(std::string filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }

    std::string line;
    std::getline(file, line);
    std::size_t line_len = line.size();
    std::vector<bool> beam_at(line_len);
    beam_at[line.find_first_of('S')] = true;
    std::uint16_t split_count = 0;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        for (std::size_t i = 0; i < line_len; ++i) {
            if (line[i] == '^' && beam_at[i]) {
                ++split_count;
                beam_at[i] = false;
                beam_at[i - 1] = true;
                beam_at[i + 1] = true;
            }
        }
    }

    return std::to_string(split_count);
}

std::string Day7::part_2(std::string filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }
    std::vector<std::string> lines;

    std::string line;
    // Skip the first line to get line_len and start_idx
    std::getline(file, line);
    std::size_t line_len = line.size();
    std::size_t start_idx = line.find_first_of('S');
    std::vector<uint64_t> timelines(line_len, 1);

    // get the rest of the file
    while (std::getline(file, line)) {
        std::getline(file, line);
        lines.push_back(line);
    }
    for (const auto &line : std::ranges::reverse_view(lines)) {
        for (std::size_t i = 0; i < line_len; ++i) {
            if (line[i] == '^') {
                // Unnecessary bound check because both test and puzzle do not have '^'
                // at the start and end of the line.
                std::uint64_t left = (i > 0) ? timelines[i - 1] : 0;
                std::uint64_t right = (i < line_len) ? timelines[i + 1] : 0;
                timelines[i] = left + right;
            }
        }
    }
    return std::to_string(timelines[start_idx]);
}