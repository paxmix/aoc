#include "day_7.hpp"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<int64_t> plus_and_mult(int64_t current, int64_t next);
std::vector<int64_t> allow_concat(int64_t current, int64_t next);

template <typename lambda>
bool dfs(int64_t target, int64_t current, const std::vector<int64_t> &nums, size_t idx, lambda get_new)
{
    if (idx == nums.size()) return current == target;
    int64_t next = nums[idx];
    for (int64_t new_current : get_new(current, next)) {
        if (dfs(target, new_current, nums, idx + 1, get_new)) return true;
    }
    return false;
}
template <typename lambda>
std::string solution(const std::string &filepath, lambda get_new)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::string line;
    int64_t sum{};
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int64_t result{};
        iss >> result;
        if (iss.peek() == ':') iss.ignore();
        int64_t num;
        std::vector<int64_t> nums{};
        while (iss >> num) {
            nums.push_back(num);
        }
        if (dfs(result, nums[0], nums, 1, get_new)) sum += result;
    }
    return std::to_string(sum);
}

std::string Day7::part_1(const std::string &filepath) { return solution(filepath, plus_and_mult); }
std::string Day7::part_2(const std::string &filepath) { return solution(filepath, allow_concat); }

std::vector<int64_t> plus_and_mult(int64_t current, int64_t next) { return {current + next, current * next}; }
std::vector<int64_t> allow_concat(int64_t current, int64_t next)
{
    std::string concat{std::to_string(current) + std::to_string(next)};
    return {current + next, current * next, std::stoll(concat)};
}