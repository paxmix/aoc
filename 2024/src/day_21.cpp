#include "day_21.hpp"
#include <fstream>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using i64 = long long;

namespace {
std::map<char, std::pair<int, int>> NUMPAD = {
    {'7', {0, 0}}, {'8', {0, 1}}, {'9', {0, 2}}, {'4', {1, 0}}, {'5', {1, 1}}, {'6', {1, 2}},
    {'1', {2, 0}}, {'2', {2, 1}}, {'3', {2, 2}}, {'0', {3, 1}}, {'A', {3, 2}},
};

std::map<char, std::pair<int, int>> DIRPAD = {
    {'^', {0, 1}}, {'A', {0, 2}}, {'<', {1, 0}}, {'v', {1, 1}}, {'>', {1, 2}},
};

// Memoization table: {from, to, depth} -> length
std::map<std::pair<std::pair<char, char>, int>, i64> memo;

// Generates valid paths between two points on a keypad
void get_paths(std::pair<int, int> start, std::pair<int, int> end, std::pair<int, int> gap, std::string current,
               std::vector<std::string> &paths)
{
    if (start == end) {
        paths.push_back(current + 'A');
        return;
    }
    // Try moving Vertically
    if (start.first != end.first) {
        int next_r = start.first + (end.first > start.first ? 1 : -1);
        if (!(next_r == gap.first && start.second == gap.second)) {
            char move = (end.first > start.first ? 'v' : '^');
            get_paths({next_r, start.second}, end, gap, current + move, paths);
        }
    }
    // Try moving Horizontally
    if (start.second != end.second) {
        int next_c = start.second + (end.second > start.second ? 1 : -1);
        if (!(start.first == gap.first && next_c == gap.second)) {
            char move = (end.second > start.second ? '>' : '<');
            get_paths({start.first, next_c}, end, gap, current + move, paths);
        }
    }
}
i64 shortest_sequence(std::string sequence, int depth, bool is_numpad)
{
    if (depth == 0) return sequence.length();

    i64 total_length = 0;
    char current_pos = 'A';
    auto &keypad = is_numpad ? NUMPAD : DIRPAD;
    std::pair<int, int> gap = is_numpad ? std::make_pair(3, 0) : std::make_pair(0, 0);
    for (char target : sequence) {
        if (memo.contains({{current_pos, target}, depth})) {
            total_length += memo[{{current_pos, target}, depth}];
        } else {
            std::vector<std::string> possible_paths;
            get_paths(keypad[current_pos], keypad[target], gap, "", possible_paths);
            i64 min_len = -1;
            for (const std::string &path : possible_paths) {
                i64 len = shortest_sequence(path, depth - 1, false);
                if (min_len == -1 || len < min_len) min_len = len;
            }
            memo[{{current_pos, target}, depth}] = min_len;
            total_length += min_len;
        }
        current_pos = target;
    }
    return total_length;
}
template <int DEPTH>
std::string solution(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::vector<std::string> codes;
    std::string line;
    while (std::getline(file, line)) {
        codes.push_back(line);
    }
    i64 total = 0;
    for (const auto &code : codes) {
        // start from the numpad
        i64 len = shortest_sequence(code, DEPTH, true);
        int num = std::stoi(code.substr(0, 3));
        total += len * num;
    }
    return std::to_string(total);
}
} // namespace

std::string Day21::part_1(const std::string &filepath) { return solution<3>(filepath); }
std::string Day21::part_2(const std::string &filepath) { return solution<26>(filepath); }