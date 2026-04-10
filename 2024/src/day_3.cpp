#include "day_3.hpp"
#include <fstream>
#include <stdexcept>
#include <string>

std::string Day3::part_1(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::string sequence{};
    int mul_sum{};
    while (std::getline(file, sequence)) {
        std::size_t i = 0;
        std::size_t len = sequence.length();
        while (i < len) {
            if (sequence.compare(i, 4, "mul(") == 0) {
                i += 4;
                std::string first, second;
                bool parsing_first{true};
                while (i < len && sequence[i] != ')') {
                    if (std::isdigit(sequence[i])) {
                        parsing_first ? first += sequence[i] : second += sequence[i];
                    } else if (sequence[i] == ',') {
                        parsing_first = false;
                    } else {
                        first.clear();
                        second.clear();
                        break;
                    }
                    ++i;
                }
                if (!first.empty() && !second.empty()) mul_sum += std::stoi(first) * std::stoi(second);
            } else {
                ++i;
            }
        }
    }
    return std::to_string(mul_sum);
}
std::string Day3::part_2(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::string sequence;
    int mul_sum{};
    bool discard = false;
    while (std::getline(file, sequence)) {
        std::size_t i = 0;
        std::size_t len = sequence.length();
        while (i < len) {
            if (!discard && sequence.compare(i, 4, "mul(") == 0) {
                i += 4;
                std::string first, second;
                bool parsing_first{true};
                while (i < len && sequence[i] != ')') {
                    if (std::isdigit(sequence[i])) {
                        parsing_first ? first += sequence[i] : second += sequence[i];
                    } else if (sequence[i] == ',') {
                        parsing_first = false;
                    } else {
                        first.clear();
                        second.clear();
                        break;
                    }
                    ++i;
                }
                if (!first.empty() && !second.empty()) mul_sum += std::stoi(first) * std::stoi(second);
            } else if (sequence.compare(i, 4, "do()") == 0) {
                discard = false;
                i += 4;
            } else if (sequence.compare(i, 7, "don't()") == 0) {
                discard = true;
                i += 7;
            } else {
                ++i;
            }
        }
    }
    return std::to_string(mul_sum);
}