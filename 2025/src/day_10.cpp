#include "day_10.hpp"

#include <bitset>
#include <charconv>
#include <fstream>
#include <queue>
#include <ranges>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

class Machine {
  public:
    Machine(const std::string &input);
    int min_presses_p1() const;
    int min_presses_p2() const;

  private:
    std::vector<std::vector<int>> buttons;
    std::vector<int> joltage_reqs;
    int diagram = 0;
    int num_switches = 0;

    static int parse_diagram(std::string_view s);
    static int parse_button(std::string_view s);
    static std::vector<int> parse_nums(std::string_view s);
};

// Part 1
std::string Day10::part_1(std::string filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }
    std::string line;
    int total_steps = 0;
    while (std::getline(file, line)) {
        total_steps += Machine(line).min_presses_p1();
    }

    return std::to_string(total_steps);
}

// Part 2
std::string Day10::part_2(std::string filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }
    std::string line;
    int total_steps = 0;
    while (std::getline(file, line)) {
        total_steps += Machine(line).min_presses_p2();
    }

    return std::to_string(total_steps);
}

Machine::Machine(const std::string &input)
{
    std::size_t i = 0;
    while (i < input.size()) {
        switch (input[i]) {
        case '[': {
            std::size_t end = input.find(']', i);
            if (end == std::string::npos) {
                throw std::runtime_error("Missing closing ']'");
            }
            std::string_view view =
                std::string_view(input).substr(i + 1, end - i - 1);
            num_switches = view.size();
            diagram = parse_diagram(view);
            i = end + 1;
        } break;
        case '(': {
            std::size_t end = input.find(')', i);
            if (end == std::string::npos) {
                throw std::runtime_error("Missing closing ')'");
            }
            buttons.push_back(
                parse_nums(std::string_view(input).substr(i + 1, end - i - 1)));
            i = end + 1;
        } break;
        case '{': {
            std::size_t end = input.find('}', i);
            if (end == std::string::npos) {
                throw std::runtime_error("Missing closing '}'");
            }
            joltage_reqs =
                parse_nums(std::string_view(input).substr(i + 1, end - i - 1));
            i = end + 1;
        } break;
        default:
            ++i;
        }
    }
}

inline int parse_binary_button(const std::vector<int> &button)
{
    int mask = 0;
    for (int b : button) {
        mask |= (1u << b);
    }
    return mask;
}

// BFS
int Machine::min_presses_p1() const
{
    std::queue<std::pair<int, int>> q; // state, steps
    std::vector<bool> visited(1 << this->num_switches, false);
    q.push({0, 0});
    visited[0] = true;
    while (!q.empty()) {
        auto [state, steps] = q.front();
        q.pop();
        if (state == this->diagram) return steps;
        for (const auto &button : buttons) {
            int mask = parse_binary_button(button);
            int next = state ^ mask;
            // if the next value already existed while doing BFS,
            // ignore the route
            if (!visited[next]) {
                visited[next] = true;
                q.push({next, steps + 1});
            }
        }
    }
    throw std::runtime_error("Machine is impossible");
}

// Part 2
class hasher {
  public:
    std::size_t operator()(const std::vector<int> &v) const
    {
        std::size_t hash = 0;
        for (std::size_t i = 0; i < v.size(); i++) {
            hash = hash * 100 + v[i];
        }
        return hash;
    }
};
class parity_hasher {
  public:
    std::size_t operator()(const std::vector<int> &v) const
    {
        std::size_t hash = 0;
        for (std::size_t i = 0; i < v.size(); i++) {
            hash = hash * 2 + (v[i] % 2);
        }
        return hash;
    }
};
std::unordered_map<std::vector<int>,
                   std::unordered_map<std::vector<int>, int, hasher>,
                   parity_hasher>
getAllParityMaps(const int n_counters,
                 const std::vector<std::vector<int>> &switches);
std::tuple<bool, int> findMinSwitchFlips(
    const std::vector<int> &current,
    const std::vector<std::vector<int>> &switches,
    const std::unordered_map<std::vector<int>,
                             std::unordered_map<std::vector<int>, int, hasher>,
                             parity_hasher> &parity_maps,
    std::unordered_map<std::vector<int>, std::tuple<bool, int>, hasher> &cache);

int Machine::min_presses_p2() const
{
    const auto parity_maps =
        getAllParityMaps(this->joltage_reqs.size(), this->buttons);
    std::unordered_map<std::vector<int>, std::tuple<bool, int>, hasher> cache;
    const auto [reached_goal, count] = findMinSwitchFlips(
        this->joltage_reqs, this->buttons, parity_maps, cache);
    return count;
}

std::unordered_map<std::vector<int>,
                   std::unordered_map<std::vector<int>, int, hasher>,
                   parity_hasher>
getAllParityMaps(const int n_counters,
                 const std::vector<std::vector<int>> &switches)
{
    std::unordered_map<std::vector<int>,
                       std::unordered_map<std::vector<int>, int, hasher>,
                       parity_hasher>
        parity_maps;
    for (int i = 0; i < (1 << switches.size()); i++) {
        std::bitset<16> bits(i);
        auto result = std::vector<int>(n_counters, 0);
        for (std::size_t j = 0; j < switches.size(); j++) {
            if (bits[j]) {
                for (const auto ele : switches[j]) {
                    result[ele]++;
                }
            }
        }
        const auto parity_map =
            result |
            std::views::transform([](const auto ele) { return ele % 2; }) |
            std::ranges::to<std::vector<int>>();
        const int n_flips = bits.count();
        if (!parity_maps[parity_map].contains(result)) {
            parity_maps[parity_map][result] = n_flips;
        } else if (parity_maps[parity_map][result] > n_flips) {
            parity_maps[parity_map][result] = n_flips;
        }
    }
    return parity_maps;
}

std::tuple<bool, int> findMinSwitchFlips(
    const std::vector<int> &current,
    const std::vector<std::vector<int>> &switches,
    const std::unordered_map<std::vector<int>,
                             std::unordered_map<std::vector<int>, int, hasher>,
                             parity_hasher> &parity_maps,
    std::unordered_map<std::vector<int>, std::tuple<bool, int>, hasher> &cache)
{
    if (cache.contains(current)) return cache[current];
    if (std::all_of(current.begin(), current.end(),
                    [](const auto ele) { return ele == 0; })) {
        cache[current] = {true, 0};
        return {true, 0};
    }
    if (std::any_of(current.begin(), current.end(),
                    [](const auto ele) { return ele < 0; })) {
        cache[current] = {false, 0};
        return {false, 0}; // exceeded goal
    }
    std::vector<int> current_parity;
    for (const auto c : current) {
        current_parity.push_back(c % 2);
    }
    if (!parity_maps.contains(current_parity)) {
        cache[current] = {false, 0};
        return {false, 0};
    }
    int min_flips = std::numeric_limits<int>::max();
    for (const auto &[pattern, n_flips] : parity_maps.at(current_parity)) {
        // Check validity (matching Python: all(i <= j for i, j in zip(pattern,
        // goal)))
        bool is_valid = true;
        for (std::size_t i = 0; i < pattern.size(); i++) {
            if (pattern[i] > current[i]) {
                is_valid = false;
                break;
            }
        }
        if (!is_valid) continue;
        // Subtract pattern from current
        auto next = current;
        for (std::size_t i = 0; i < pattern.size(); i++) {
            next[i] = next[i] - pattern[i];
        }
        // After subtracting matching parity pattern, result is all even -
        // divide immediately
        for (auto &ele : next) {
            ele /= 2;
        }

        const auto [reached_goal, count] =
            findMinSwitchFlips(next, switches, parity_maps, cache);
        if (reached_goal) min_flips = std::min(min_flips, n_flips + 2 * count);
    }
    if (min_flips == std::numeric_limits<int>::max()) {
        cache[current] = {false, 0};
        return {false, 0};
    }
    cache[current] = {true, min_flips};
    return {true, min_flips};
};

// Parsing
int Machine::parse_diagram(std::string_view s)
{
    int mask = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '#') {
            mask |= (1u << i);
        }
    }
    return mask;
}

std::vector<int> Machine::parse_nums(std::string_view s)
{
    std::vector<int> nums;
    const char *ptr = s.data();
    const char *end = ptr + s.size();
    while (ptr < end) {
        int value = 0;
        auto [next, ec] = std::from_chars(ptr, end, value);
        if (ec != std::errc()) throw std::runtime_error("Invalid number");
        nums.push_back(value);
        ptr = next;
        if (ptr < end && *ptr == ',') {
            ++ptr;
        }
    }
    return nums;
}
