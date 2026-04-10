#include "day_15.hpp"
#include <deque>
#include <fstream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
constexpr char WALL = '#';
constexpr char BOX = 'O';
constexpr char EMPTY = '.';
constexpr char ROBOT = '@';

class Robot {
  public:
    Robot(size_t x = 0, size_t y = 0) : x_(x), y_(y) {}
    void move(std::vector<std::string> &map, int dx, int dy)
    {
        int nx = x_ + dx;
        int ny = y_ + dy;
        int tx = nx;
        int ty = ny;
        while (map[tx][ty] == BOX) {
            tx += dx;
            ty += dy;
        }
        if (map[tx][ty] == WALL) return;
        if (map[tx][ty] == EMPTY) {
            if (map[nx][ny] == BOX) map[tx][ty] = BOX;
            map[nx][ny] = ROBOT;
            map[x_][y_] = EMPTY;
            x_ = nx;
            y_ = ny;
        }
    }

  private:
    int x_;
    int y_;
};

struct Pos {
    int x_, y_;
    bool operator<(const Pos &other) const { return x_ < other.x_ || (x_ == other.x_ && y_ < other.y_); }
};
class Warehouse {
  public:
    void move(int dx, int dy)
    {
        int nx = robot_x_ + dx;
        int ny = robot_y_ + dy;

        if (map_[nx][ny] == '#') return;

        if (map_[nx][ny] == '.') {
            update_robot(nx, ny);
            return;
        }

        // It's a box ('[' or ']')
        if (dx == 0) {
            // Horizontal move: identical logic to Part 1, just scan further
            int ty = ny;
            while (map_[nx][ty] == '[' || map_[nx][ty] == ']')
                ty += dy;

            if (map_[nx][ty] == '#') return;
            if (map_[nx][ty] == '.') {
                // Shift everything in the row
                for (int y = ty; y != robot_y_; y -= dy) {
                    map_[nx][y] = map_[nx][y - dy];
                }
                update_robot(nx, ny);
            }
        } else {
            // Vertical move: The "Wide Box" Cascade
            std::set<Pos> boxes_to_move;
            std::deque<Pos> queue;
            queue.emplace_back(robot_x_, robot_y_);

            bool can_move = true;
            std::set<Pos> seen;

            while (!queue.empty()) {
                Pos curr = queue.front();
                queue.pop_front();

                if (seen.count(curr)) continue;
                seen.insert(curr);

                int next_x = curr.x_ + dx;
                int next_y = curr.y_;

                if (map_[next_x][next_y] == '#') {
                    can_move = false;
                    break;
                }

                if (map_[next_x][next_y] == '[') {
                    queue.emplace_back(next_x, next_y);
                    queue.emplace_back(next_x, next_y + 1); // Add the other half
                    boxes_to_move.insert({next_x, next_y});
                    boxes_to_move.insert({next_x, next_y + 1});
                } else if (map_[next_x][next_y] == ']') {
                    queue.emplace_back(next_x, next_y);
                    queue.emplace_back(next_x, next_y - 1); // Add the other half
                    boxes_to_move.insert({next_x, next_y});
                    boxes_to_move.insert({next_x, next_y - 1});
                }
            }

            if (can_move) {
                // Move boxes from back to front to avoid overwriting
                std::vector<std::string> next_map = map_;
                for (auto const &pos : boxes_to_move)
                    next_map[pos.x_][pos.y_] = '.';
                for (auto const &pos : boxes_to_move) {
                    next_map[pos.x_ + dx][pos.y_] = map_[pos.x_][pos.y_];
                }
                map_ = next_map;
                update_robot(nx, ny);
            }
        }
    }

    std::vector<std::string> map_;
    int robot_x_, robot_y_;

  private:
    void update_robot(int nr, int nc)
    {
        map_[robot_x_][robot_y_] = '.';
        robot_x_ = nr;
        robot_y_ = nc;
        map_[robot_x_][robot_y_] = '@';
    }
};
} // namespace

std::string Day15::part_1(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::string line;
    std::vector<std::string> map;
    Robot robot{};
    while (std::getline(file, line)) {
        if (line.empty()) break;
        if (line.find(ROBOT) != std::string::npos) {
            robot = Robot{map.size(), line.find(ROBOT)};
        }
        map.push_back(line);
    }
    while (std::getline(file, line)) {
        for (char dir : line) {
            switch (dir) {
            case '^': {
                robot.move(map, -1, 0);
            } break;
            case '>': {
                robot.move(map, 0, 1);
            } break;
            case 'v': {
                robot.move(map, 1, 0);
            } break;
            case '<': {
                robot.move(map, 0, -1);
            } break;
            }
        }
    }
    long long gps_sum = 0;
    for (std::size_t i = 1; i < map.size() - 1; ++i) {
        for (std::size_t j = 1; j < map[0].size() - 1; ++j) {
            if (map[i][j] == BOX) gps_sum += i * 100 + j;
        }
    }
    return std::to_string(gps_sum);
}
std::string Day15::part_2(const std::string &filepath)
{
    std::ifstream file(filepath);
    std::string line;
    Warehouse wh;

    // 1. Scaled Parsing
    while (std::getline(file, line) && !line.empty()) {
        std::string row;
        for (char c : line) {
            if (c == WALL) {
                row += "##";
            } else if (c == BOX) {
                row += "[]";
            } else if (c == EMPTY) {
                row += "..";
            } else if (c == ROBOT) {
                row += "@.";
            }
        }
        if (row.find('@') != std::string::npos) {
            wh.robot_x_ = wh.map_.size();
            wh.robot_y_ = row.find('@');
        }
        wh.map_.push_back(row);
    }

    // 2. Execute Moves
    while (std::getline(file, line)) {
        for (char dir : line) {
            switch (dir) {
            case '^': {
                wh.move(-1, 0);
            } break;
            case '>': {
                wh.move(0, 1);
            } break;
            case 'v': {
                wh.move(1, 0);
            } break;
            case '<': {
                wh.move(0, -1);
            } break;
            }
        }
    }

    long long sum = 0;
    for (std::size_t x = 1; x < wh.map_.size() - 1; ++x) {
        for (std::size_t y = 2; y < wh.map_[0].size() - 2; ++y) {
            if (wh.map_[x][y] == '[') sum += (100 * x + y);
        }
    }
    return std::to_string(sum);
}