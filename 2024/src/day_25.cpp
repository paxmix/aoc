#include "day_25.hpp"
#include <array>
#include <cstddef>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

std::string Day25::part_1(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::vector<std::array<int, 5>> locks;
    std::vector<std::array<int, 5>> keys;
    std::string line;
    while (std::getline(file, line)) {
        bool is_lock = line == "#####";
        std::array<int, 5> schematic{};
        do {
            for (size_t i = 0; i < 5; ++i) {
                if (line[i] == '#') ++schematic[i];
            }
        } while (std::getline(file, line) && !line.empty());
        for (int &val : schematic) {
            --val;
        }
        is_lock ? locks.push_back(schematic) : keys.push_back(schematic);
    }
    int count = 0;
    for (const auto &lock : locks) {
        for (const auto &key : keys) {
            bool fit = true;
            for (int i = 0; i < 5; ++i) {
                if (lock[i] + key[i] > 5) {
                    fit = false;
                    break;
                }
            }
            if (fit) ++count;
        }
    }
    return std::to_string(count);
}
std::string Day25::part_2(const std::string &filepath) { return ""; }