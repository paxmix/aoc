#include "day_23.hpp"
#include <array>
#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

namespace {
constexpr int MAX_ID = 26 * 26;
int to_id(const std::string &name) { return (name[0] - 'a') * 26 + (name[1] - 'a'); }
std::string from_id(int id)
{
    std::string name{2, ' '};
    name[0] = 'a' + id / 26;
    name[1] = 'a' + id % 26;
    return name;
}
// R: The current clique we are building.
// P: The set of candidate nodes that could be added to R.
// X: The set of nodes already processed.
void bron_kerbosch(std::vector<int> R, std::vector<int> P, std::vector<int> X,
                   const std::array<std::array<bool, MAX_ID>, MAX_ID> &connected, std::vector<int> &max_clique)
{
    if (P.empty() && X.empty() && R.size() > max_clique.size()) max_clique = R;
    if (P.empty()) return;
    // Pivoting to prune the search: Choose a pivot 'u' from P U X
    int pivot = P[0];
    // We only need to test nodes in P that are NOT neighbors of the pivot
    std::vector<int> candidates;
    for (int v : P) {
        if (!connected[pivot][v]) candidates.push_back(v);
    }
    for (int v : candidates) {
        std::vector<int> next_R = R;
        next_R.push_back(v);
        std::vector<int> next_P, next_X;
        for (int p : P) {
            if (connected[v][p]) next_P.push_back(p);
        }
        for (int x : X) {
            if (connected[v][x]) next_X.push_back(x);
        }
        bron_kerbosch(next_R, next_P, next_X, connected, max_clique);
        // Move v from P to X
        if (auto it = std::find(P.begin(), P.end(), v); it != P.end()) P.erase(it);
        X.push_back(v);
    }
}
} // namespace

std::string Day23::part_1(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file");
    std::array<std::vector<int>, MAX_ID> adj;
    std::array<std::array<bool, MAX_ID>, MAX_ID> connected{};
    std::unordered_set<int> nodes;
    std::string line;
    while (std::getline(file, line)) {
        int i = to_id(line.substr(0, 2));
        int j = to_id(line.substr(3, 2));
        adj[i].push_back(j);
        adj[j].push_back(i);
        connected[i][j] = connected[j][i] = true;
        nodes.insert(i);
        nodes.insert(j);
    }
    int count = 0;
    int t_start = ('t' - 'a') * 26;
    int t_end = t_start + 26;
    for (int a : nodes) {
        auto &neighbors = adj[a];
        // sort so we can properly check unique triplets
        std::sort(neighbors.begin(), neighbors.end());
        for (std::size_t j = 0; j < neighbors.size(); ++j) {
            int b = neighbors[j];
            // Enforce ordering: only look at neighbors 'greater' than a
            if (b <= a) continue;
            for (std::size_t k = j + 1; k < neighbors.size(); ++k) {
                int c = neighbors[k];
                // Enforce ordering: only look at neighbors 'greater' than b
                if (c <= b) continue;
                if (connected[b][c] &&
                    ((a >= t_start && a < t_end) || (b >= t_start && b < t_end) || (c >= t_start && c < t_end))) {
                    ++count;
                }
            }
        }
    }
    return std::to_string(count);
}
std::string Day23::part_2(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::array<std::array<bool, MAX_ID>, MAX_ID> connected{};
    std::vector<int> nodes;
    std::array<bool, MAX_ID> existed{};
    std::string line;
    while (std::getline(file, line)) {
        int i = to_id(line.substr(0, 2));
        int j = to_id(line.substr(3, 2));
        connected[i][j] = connected[j][i] = true;
        if (!existed[i]) {
            existed[i] = true;
            nodes.push_back(i);
        }
        if (!existed[j]) {
            existed[j] = true;
            nodes.push_back(j);
        }
    }
    std::vector<int> max_clique;
    bron_kerbosch({}, nodes, {}, connected, max_clique);
    std::sort(max_clique.begin(), max_clique.end());
    std::string password;
    for (std::size_t i = 0; i < max_clique.size(); ++i) {
        password += from_id(max_clique[i]) + (i == max_clique.size() - 1 ? "" : ",");
    }
    return password;
}