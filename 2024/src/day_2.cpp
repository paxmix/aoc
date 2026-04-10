#include "day_2.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

bool is_valid(const std::vector<int> &report);

std::string Day2::part_1(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::string line{};
    int safe_count{};
    while (std::getline(file, line)) {
        std::vector<int> report{};
        std::istringstream ss{line};
        int num{};
        while (ss >> num) {
            report.push_back(num);
        }
        if (is_valid(report)) ++safe_count;
    }
    return std::to_string(safe_count);
}
std::string Day2::part_2(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::string line{};
    int safe_count{};
    while (std::getline(file, line)) {
        std::vector<int> report{};
        int num;
        std::istringstream ss{line};
        while (ss >> num) {
            report.push_back(num);
        }
        if (is_valid(report)) {
            ++safe_count;
            continue;
        }
        bool ok{};
        for (std::size_t i = 0; i < report.size(); ++i) {
            std::vector<int> temp{report};
            temp.erase(temp.begin() + i);
            if (is_valid(temp)) {
                ok = true;
                break;
            }
        }
        if (ok) ++safe_count;
    }
    return std::to_string(safe_count);
}
bool is_valid(const std::vector<int> &report)
{
    int diff = report[1] - report[0];
    if (diff == 0 || std::abs(diff) > 3) return false;
    bool is_ascend = diff > 0;
    for (std::size_t i = 2; i < report.size(); ++i) {
        diff = report[i] - report[i - 1];
        if (diff == 0 || std::abs(diff) > 3) return false;
        if ((diff > 0) != is_ascend) return false;
    }
    return true;
}