#include "day_5.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::unordered_map<int, std::unordered_set<int>> get_update_order(std::basic_ifstream<char> &file, std::string &line);
std::vector<int> get_update(std::string &line);
bool is_valid(const std::vector<int> &update, const std::unordered_map<int, std::unordered_set<int>> &update_order);

std::string Day5::part_1(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::string line;
    auto update_order = get_update_order(file, line);
    int mid_sum{};
    while (std::getline(file, line)) {
        auto update = get_update(line);
        if (is_valid(update, update_order)) mid_sum += update[update.size() / 2];
    }
    return std::to_string(mid_sum);
}
std::string Day5::part_2(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::string line;
    auto update_order = get_update_order(file, line);
    int mid_sum{};
    while (std::getline(file, line)) {
        auto update = get_update(line);
        if (!is_valid(update, update_order)) {
            std::vector<int> fixed_update{update};
            std::sort(fixed_update.begin(), fixed_update.end(),
                      [&update_order](int prev, int next) { return update_order[prev].contains(next); });
            mid_sum += fixed_update[fixed_update.size() / 2];
        };
    }
    return std::to_string(mid_sum);
}
std::unordered_map<int, std::unordered_set<int>> get_update_order(std::basic_ifstream<char> &file, std::string &line)
{
    std::unordered_map<int, std::unordered_set<int>> update_order;
    while (std::getline(file, line) && !line.empty()) {
        std::istringstream iss(line);
        int key, val;
        char bar;
        iss >> key >> bar >> val;
        update_order[key].insert(val);
    }
    return update_order;
}
std::vector<int> get_update(std::string &line)
{
    std::vector<int> update;
    std::istringstream iss(line);
    std::string token;
    while (std::getline(iss, token, ',')) {
        int val = std::stoi(token);
        update.push_back(val);
    }
    return update;
}
bool is_valid(const std::vector<int> &update, const std::unordered_map<int, std::unordered_set<int>> &update_order)
{
    int len = static_cast<int>(update.size());
    for (int i = 0; i < len; ++i) {
        auto it = update_order.find(update[i]);
        for (int j = i + 1; j < len; ++j) {
            if (it == update_order.end() || !it->second.contains(update[j])) {
                return false;
            }
        }
    }
    return true;
}