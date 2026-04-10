#include "day_1.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

std::pair<std::vector<int>, std::vector<int>> get_vecs(const std::string &filepath);

std::string Day1::part_1(const std::string &filepath)
{
    auto [left, right] = get_vecs(filepath);
    if (left.empty() || right.empty()) return "";
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    int diff{};
    for (std::size_t i = 0; i < left.size(); ++i) {
        diff += std::abs(left[i] - right[i]);
    }
    return std::to_string(diff);
}
std::string Day1::part_2(const std::string &filepath)
{
    auto [left, right] = get_vecs(filepath);
    if (left.empty() || right.empty()) return "";
    std::unordered_map<int, int> freqs{};
    for (int val : right) {
        ++freqs[val];
    }
    int simil{};
    for (int val : left) {
        simil += val * freqs[val];
    }
    return std::to_string(simil);
}
std::pair<std::vector<int>, std::vector<int>> get_vecs(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return {};
    }
    std::vector<int> left{};
    std::vector<int> right{};
    std::string line{};
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        int first, second;
        ss >> first >> second;
        left.push_back(first);
        right.push_back(second);
    }
    return {left, right};
}
