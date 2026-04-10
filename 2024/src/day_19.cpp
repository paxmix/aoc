#include "day_19.hpp"
#include <cctype>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

using i64 = long long;

namespace {
std::vector<std::string> get_patterns(const std::string &line)
{
    std::vector<std::string> patterns;
    std::string curr;
    for (char c : line) {
        if (c == ',' && !curr.empty()) {
            patterns.push_back(curr);
            curr.clear();
        }
        if (std::isalpha(c)) curr.push_back(c);
    }
    if (!curr.empty()) patterns.push_back(curr);
    return patterns;
}
bool possible_design(std::size_t start, const std::string &design, const std::vector<std::string> &patterns,
                     std::vector<int> &memo)
{
    if (start == design.size()) return true;
    if (memo[start] != -1) return memo[start];
    for (const auto &pattern : patterns) {
        if (design.compare(start, pattern.size(), pattern) == 0 &&
            possible_design(start + pattern.size(), design, patterns, memo)) {
            memo[start] = 1;
            return true;
        }
    }
    memo[start] = 0;
    return false;
}
i64 design_count(std::size_t start, const std::string &design, const std::vector<std::string> &patterns,
                 std::vector<i64> &memo)
{
    if (start == design.size()) return 1;
    if (memo[start] != -1) return memo[start];
    i64 total_ways = 0;
    for (const auto &pattern : patterns) {
        if (design.compare(start, pattern.size(), pattern) == 0) {
            total_ways += design_count(start + pattern.size(), design, patterns, memo);
        }
    }
    return memo[start] = total_ways;
}
} // namespace

std::string Day19::part_1(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::string line;
    std::getline(file, line);
    auto patterns = get_patterns(line);
    int count = 0;
    std::getline(file, line);
    while (std::getline(file, line)) {
        // memo act like a map<std::size_t,bool>, -1 is uninitialized, 0 is false, 1 is true
        std::vector<int> memo(line.size(), -1);
        if (possible_design(0, line, patterns, memo)) ++count;
    }
    return std::to_string(count);
}
std::string Day19::part_2(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::string line;
    std::getline(file, line);
    auto patterns = get_patterns(line);
    std::getline(file, line);
    i64 total = 0;
    while (std::getline(file, line)) {
        // memo act like a map<std::size_t,i64>, -1 is uninitialized, other is count of possible design ways
        std::vector<i64> memo(line.size(), -1);
        total += design_count(0, line, patterns, memo);
    }
    return std::to_string(total);
}