#include "day_11.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using i64 = std::int64_t;

class Graph {
  public:
    Graph(const std::string &filepath);
    i64 count_paths_p1(const std::string &start, const std::string &end);
    i64 count_paths_p2(const std::string &start, const std::string &end,
                       const std::pair<std::string, std::string> &must_visit);

  private:
    std::unordered_map<std::string, int> id;
    std::vector<std::vector<int>> paths;

    i64 dfs(int node, int end, std::vector<i64> &memo);
    i64 dfs_viaAB(int node, int end, int A, int B, int mask,
                  std::vector<std::array<i64, 4>> &memo);
    int get_id(const std::string &node);
};

constexpr const char *YOU = "you";
constexpr const char *OUT = "out";
std::string Day11::part_1(std::string filepath)
{
    return std::to_string(Graph{filepath}.count_paths_p1(YOU, OUT));
}

constexpr const char *SVR = "svr";
constexpr std::pair<const char *, const char *> MUST_VISIT = {"dac", "fft"};
std::string Day11::part_2(std::string filepath)
{
    return std::to_string(Graph{filepath}.count_paths_p2(SVR, OUT, MUST_VISIT));
}

// Part 1
i64 Graph::count_paths_p1(const std::string &start, const std::string &end)
{
    std::vector<i64> memo(this->paths.size(), -1);
    return this->dfs(this->get_id(start), this->get_id(end), memo);
}
i64 Graph::dfs(int node, int end, std::vector<i64> &memo)
{
    if (node == end) return 1;
    if (memo[node] != -1) return memo[node];
    i64 total = 0;
    for (int next : this->paths[node]) {
        total += this->dfs(next, end, memo);
    }
    return total;
}

// Part 2
i64 Graph::count_paths_p2(const std::string &start, const std::string &end,
                          const std::pair<std::string, std::string> &must_visit)
{
    std::vector<std::array<i64, 4>> memo(this->paths.size(), {-1, -1, -1, -1});
    return this->dfs_viaAB(this->get_id(start), this->get_id(end),
                           this->get_id(must_visit.first),
                           this->get_id(must_visit.second), 0, memo);
}
i64 Graph::dfs_viaAB(int node, int end, int A, int B, int mask,
                     std::vector<std::array<i64, 4>> &memo)
{
    if (node == A || node == B) mask |= (node == A ? 1 : 2);
    if (node == end) return mask == 3;
    auto &res = memo[node][mask];
    if (res != -1) return res;
    i64 total = 0;
    for (int next : this->paths[node]) {
        total += dfs_viaAB(next, end, A, B, mask, memo);
    }
    return res = total;
}

Graph::Graph(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string node, token;
        if (!(iss >> token)) continue;
        if (token.back() != ':') continue;
        node = token.substr(0, token.size() - 1);
        int node_id = get_id(node);
        while (iss >> token) {
            int neighbor_id = get_id(token);
            this->paths[node_id].push_back(neighbor_id);
        }
    }
}

int Graph::get_id(const std::string &node)
{
    if (auto it = this->id.find(node); it != this->id.end()) return it->second;
    int new_id = this->paths.size();
    this->id[node] = new_id;
    this->paths.emplace_back();
    return new_id;
}