#include "day_8.hpp"

#include <cstddef>
#include <fstream>
#include <functional>
#include <ios>
#include <iostream>
#include <iterator>
#include <queue>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>

using i64 = std::int64_t;

class JBox {
  public:
    i64 x;
    i64 y;
    i64 z;

    explicit JBox(const std::string_view &input)
    {
        const char *ptr = input.data();
        const char *end = ptr + input.size();
        auto [p1, ec1] = std::from_chars(ptr, end, x);
        if (ec1 != std::errc{} || p1 == end || *p1 != ',') {
            throw std::runtime_error("Invalid JBox format: " +
                                     std::string(input));
        }
        auto [p2, ec2] = std::from_chars(p1 + 1, end, y);
        if (ec2 != std::errc{} || p2 == end || *p2 != ',') {
            throw std::runtime_error("Invalid JBox format: " +
                                     std::string(input));
        }
        auto [_, ec3] = std::from_chars(p2 + 1, end, z);
        if (ec3 != std::errc{}) {
            throw std::runtime_error("Invalid JBox format: " +
                                     std::string(input));
        }
    }
};

template <typename T>
class DisjointSetUnion {
  private:
    std::size_t size;
    std::vector<std::size_t> parent;
    std::vector<std::size_t> comp_size;

  public:
    explicit DisjointSetUnion(std::vector<T> values)
        : size(values.size()), parent(size), comp_size(size, 1)
    {
        for (std::size_t i = 0; i < parent.size(); ++i) {
            parent[i] = i;
        }
    }

    std::size_t len() const { return size; }

    std::size_t root_of(std::size_t x)
    {
        return parent[x] != x ? parent[x] = root_of(parent[x]) : x;
    }

    bool join(std::size_t a, std::size_t b)
    {
        size_t root_a = root_of(a);
        size_t root_b = root_of(b);
        if (root_a == root_b) {
            return false;
        }

        if (comp_size[root_a] < comp_size[root_b]) {
            std::swap(root_a, root_b);
        }
        parent[root_b] = root_a;
        comp_size[root_a] += comp_size[root_b];
        return true;
    }

    std::size_t component_size(std::size_t x) { return comp_size[root_of(x)]; }
};

i64 square_distance(const JBox &a, const JBox &b)
{
    i64 dx = a.x - b.x;
    i64 dy = a.y - b.y;
    i64 dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

std::vector<std::tuple<i64, size_t, size_t>>
get_distances(const std::vector<JBox> &boxes)
{
    std::vector<std::tuple<i64, size_t, size_t>> distances;
    std::size_t n = boxes.size();
    distances.reserve(n * (n - 1) / 2);
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = i + 1; j < n; ++j) {
            distances.emplace_back(square_distance(boxes[i], boxes[j]), i, j);
        }
    }
    std::sort(distances.begin(), distances.end());
    return distances;
}

std::priority_queue<std::tuple<i64, size_t, size_t>>
get_distances_p1(const std::vector<JBox> &boxes, std::size_t limit)
{
    std::priority_queue<std::tuple<i64, size_t, size_t>> heap;
    for (size_t i = 0; i < boxes.size(); ++i) {
        for (size_t j = i + 1; j < boxes.size(); ++j) {
            auto e = std::make_tuple(square_distance(boxes[i], boxes[j]), i, j);
            if (heap.size() < limit) {
                heap.push(e);
            } else if (std::get<0>(e) < std::get<0>(heap.top())) {
                heap.pop();
                heap.push(e);
            }
        }
    }
    return heap;
}

std::string Day8::part_1(std::string filepath)
{
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    const char *ptr = content.data();
    const char *end = ptr + content.size();
    std::vector<JBox> boxes;
    while (ptr < end) {
        const char *line_end = std::find(ptr, end, '\n');
        std::string_view line(ptr, line_end - ptr);
        boxes.emplace_back(line);
        ptr = (line_end == end) ? end : line_end + 1;
    }
    DisjointSetUnion<JBox> dsu(boxes);
    auto pq = get_distances_p1(boxes, this->max_union);
    while (!pq.empty()) {
        auto [dist, i, j] = pq.top();
        dsu.join(i, j);
        pq.pop();
    }
    std::size_t dsu_len = dsu.len();
    std::vector<std::size_t> counts(dsu_len);
    for (std::size_t i = 0; i < dsu_len; ++i) {
        counts[dsu.root_of(i)]++;
    }
    std::sort(counts.begin(), counts.end(), std::greater<>());
    std::size_t result = 1;
    for (std::size_t i = 0; i < 3; ++i) {
        result *= counts[i];
    }

    return std::to_string(result);
}

std::string Day8::part_2(std::string filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    const char *ptr = content.data();
    const char *end = ptr + content.size();
    std::vector<JBox> boxes;
    while (ptr < end) {
        const char *line_end = std::find(ptr, end, '\n');
        std::string_view line(ptr, line_end - ptr);
        boxes.emplace_back(line);

        ptr = (line_end == end) ? end : line_end + 1;
    }
    DisjointSetUnion<JBox> dsu(boxes);
    std::size_t last_i = 0;
    std::size_t last_j = 0;
    for (auto &[_dist, i, j] : get_distances(boxes)) {
        if (dsu.join(i, j) && dsu.component_size(0) == boxes.size()) {
            last_i = i;
            last_j = j;
            break;
        }
    }

    return std::to_string(boxes[last_i].x * boxes[last_j].x);
}
