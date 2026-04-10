#include "day_8.hpp"
#include <cctype>
#include <fstream>
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace {
struct pair_hash {
    std::size_t operator()(const std::pair<int, int> &coor) const
    {
        auto [x, y] = coor;
        std::size_t hash{};
        hash ^= std::hash<int>{}(x) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= std::hash<int>{}(y) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        return hash;
    }
};
std::unordered_map<char, std::vector<std::pair<int, int>>> get_freqs(const std::string &filepath, int &row, int &col)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::unordered_map<char, std::vector<std::pair<int, int>>> freqs;
    std::string line;
    while (std::getline(file, line)) {
        col = line.length();
        for (int i = 0; i < col; ++i) {
            if (std::isalnum(line[i])) freqs[line[i]].emplace_back(row, i);
        }
        ++row;
    }
    return freqs;
}
bool is_valid(int x, int y, int row, int col) { return x >= 0 && y >= 0 && x < row && y < col; }
template <bool Harmonic>
static std::vector<std::pair<int, int>> get_antinodes(const std::pair<int, int> &coor_a,
                                                      const std::pair<int, int> &coor_b, int row, int col)
{
    std::vector<std::pair<int, int>> antinodes;
    auto [ax, ay] = coor_a;
    auto [bx, by] = coor_b;
    int dx = bx - ax;
    int dy = by - ay;
    for (int k = Harmonic ? 0 : 1; is_valid(bx + k * dx, by + k * dy, row, col); ++k) {
        antinodes.emplace_back(bx + k * dx, by + k * dy);
        if constexpr (!Harmonic) break;
    }
    for (int k = Harmonic ? 0 : 1; is_valid(ax - k * dx, ay - k * dy, row, col); ++k) {
        antinodes.emplace_back(ax - k * dx, ay - k * dy);
        if constexpr (!Harmonic) break;
    }
    return antinodes;
}
template <bool Harmonic>
std::string solution(const std::string &filepath)
{
    int row{}, col{};
    auto freqs = get_freqs(filepath, row, col);
    std::unordered_set<std::pair<int, int>, pair_hash> antinodes{};
    for (auto it = freqs.begin(); it != freqs.end(); ++it) {
        const auto &coors = it->second;
        int len = coors.size();
        for (int i = 0; i < len; ++i) {
            for (int j = i + 1; j < len; ++j) {
                auto antis = get_antinodes<Harmonic>(coors[i], coors[j], row, col);
                antinodes.insert(antis.begin(), antis.end());
            }
        }
    }
    return std::to_string(antinodes.size());
}
} // namespace

std::string Day8::part_1(const std::string &filepath) { return solution<false>(filepath); }
std::string Day8::part_2(const std::string &filepath) { return solution<true>(filepath); }