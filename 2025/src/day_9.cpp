#include "day_9.hpp"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <queue>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using usize = std::size_t;

class Point {
  public:
    i64 x;
    i64 y;

    Point() = default;
    Point(i64 x, i64 y) : x(x), y(y) {}
    // Construct from "x,y" string
    Point(const std::string &input)
    {
        const char *ptr = input.data();
        const char *end = ptr + input.size();
        auto [p1, ec1] = std::from_chars(ptr, end, x);
        if (ec1 != std::errc{} || p1 == end || *p1 != ',') {
            throw std::runtime_error{"Invalid point format: " + input};
        }
        auto [_, ec2] = std::from_chars(p1 + 1, end, y);
        if (ec2 != std::errc{}) {
            throw std::runtime_error{"Invalid point format: " + input};
        }
    }

    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }
};

u64 rect_area(const Point &a, const Point &b)
{
    u64 dx = std::abs(a.x - b.x) + 1;
    u64 dy = std::abs(a.y - b.y) + 1;
    return dx * dy;
}

u64 find_max_area(const std::vector<Point> &points)
{
    u64 max_area = 0;
    for (usize i = 0; i < points.size(); ++i) {
        for (usize j = i + 1; j < points.size(); ++j) {
            max_area = std::max(max_area, rect_area(points[i], points[j]));
        }
    }
    return max_area;
}

std::string Day9::part_1(std::string filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error{"Failed to open file: " + filepath};
    }
    std::vector<Point> points;
    std::string line;
    while (std::getline(file, line)) {
        points.emplace_back(line);
    }
    return std::to_string(find_max_area(points));
}

std::vector<Point> compress_points(const std::vector<Point> &points)
{
    // deduplicate and sort by using a set
    std::set<i64> cols;
    std::set<i64> rows;
    std::vector<Point> compressed_points;
    compressed_points.reserve(points.size());
    for (const auto &p : points) {
        rows.insert(p.x);
        cols.insert(p.y);
    }
    for (const auto &p : points) {
        compressed_points.emplace_back(
            std::distance(std::begin(rows), rows.find(p.x)),
            std::distance(std::begin(cols), cols.find(p.y)));
    }
    return compressed_points;
}

std::vector<std::vector<i64>> create_map(const std::vector<Point> &points)
{
    const auto row_max =
        (*std::max_element(
             std::begin(points), std::end(points),
             [](const auto &p1, const auto &p2) { return p1.x < p2.x; }))
            .x;
    const auto col_max =
        (*std::max_element(
             std::begin(points), std::end(points),
             [](const auto &p1, const auto &p2) { return p1.y < p2.y; }))
            .y;

    auto map = std::vector<std::vector<i64>>(row_max + 1,
                                             std::vector<i64>(col_max + 1, 0));
    for (std::size_t i = 1; i < points.size(); ++i) {
        const auto d_r = points[i].x - points[i - 1].x;
        const auto d_c = points[i].y - points[i - 1].y;
        const auto delta = Point{
            (d_r != 0) ? d_r / std::abs(d_r) : 0,
            (d_c != 0) ? d_c / std::abs(d_c) : 0,
        };
        auto current = points[i - 1];
        while (current != points[i]) {
            // std::cout << current[0] << ' ' << current[1] << '\n';
            map[current.x][current.y] = 1;
            current.x += delta.x;
            current.y += delta.y;
        }
    }
    return map;
}

void flood_fill(std::vector<std::vector<i64>> &map)
{
    // get starting point
    Point p{0, 0};
    {
        i64 idx = 0;
        while (map[idx][0] == 0) {
            ++idx;
        }
        p = {idx + 1, 1};
    }
    std::queue<Point> q;
    q.push(p);
    const std::vector<Point> adj_delta{{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
    while (!q.empty()) {
        const auto c = q.front();
        q.pop();
        map[c.x][c.y] = 2;
        for (const auto &d : adj_delta) {
            const auto n = Point{c.x + d.x, c.y + d.y};
            if (n.x >= 0 && n.x < static_cast<i64>(map.size()) && n.y >= 0 &&
                n.y < static_cast<i64>(map[0].size()) && map[n.x][n.y] == 0) {
                q.push(n);
                map[n.x][n.y] = -1;
            }
        }
    }
}

bool is_valid_rect(const std::vector<std::vector<i64>> &map, const Point &p1,
                   const Point &p2)
{
    for (int r = std::min(p1.x, p2.x); r <= std::max(p1.x, p2.x); ++r) {
        for (int c = std::min(p1.y, p2.y); c <= std::max(p1.y, p2.y); ++c) {
            if (map[r][c] == 0) return false;
        }
    }
    return true;
}

u64 max_area_p2(const std::vector<std::vector<i64>> &map,
                const std::vector<Point> &compressed_points,
                const std::vector<Point> &points)
{
    u64 area = 0;
    for (usize i = 0; i < points.size(); ++i) {
        for (usize j = i + 1; j < points.size(); ++j) {
            u64 new_area = rect_area(points[i], points[j]);
            if (new_area > area && is_valid_rect(map, compressed_points[i],
                                                 compressed_points[j])) {
                area = new_area;
            }
        }
    }
    return area;
}

std::string Day9::part_2(std::string filepath)
{
    std::string line;
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error{"Failed to open file: " + filepath};
    }

    std::vector<Point> points;
    while (std::getline(file, line)) {
        points.emplace_back(line);
    }
    points.push_back(points[0]); // Close the polygon
    const auto compressed_points = compress_points(points);
    auto map = create_map(compressed_points);
    flood_fill(map);

    return std::to_string(max_area_p2(map, compressed_points, points));
}
