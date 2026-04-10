#include "day_9.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
std::vector<int> get_files(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::string line;
    std::getline(file, line);
    int id{0};
    std::vector<int> files;
    bool is_file{true};
    for (char c : line) {
        int len = c - '0';
        if (is_file) {
            for (int i = 0; i < len; ++i) {
                files.push_back(id);
            }
            ++id;
        } else {
            for (int i = 0; i < len; ++i) {
                files.push_back(-1);
            }
        }
        is_file = !is_file;
    }
    return files;
}
struct Block {
    int id;
    int pos;
    int len;
};
} // namespace

std::string Day9::part_1(const std::string &filepath)
{
    auto files = get_files(filepath);
    int left{0};
    int right = files.size() - 1;
    int64_t checksum{0};
    while (left <= right) {
        if (files[left] != -1) {
            checksum += static_cast<int64_t>(files[left]) * left;
            ++left;
        } else if (files[right] == -1) {
            --right;
        } else {
            files[left] = files[right];
            --right;
        }
    }
    return std::to_string(checksum);
}
std::string Day9::part_2(const std::string &filepath)
{
    std::ifstream file(filepath);
    std::string line;
    std::getline(file, line);
    std::vector<Block> files;
    // free_slots[length] stores the starting positions of gaps of that exact length
    std::array<std::vector<int>, 10> free_slots;
    int current_pos = 0;
    int file_id = 0;
    bool is_file = true;
    for (char c : line) {
        int len = c - '0';
        if (is_file) {
            files.push_back({file_id++, current_pos, len});
        } else if (len > 0) {
            free_slots[len].push_back(current_pos);
        }
        current_pos += len;
        is_file = !is_file;
    }
    // Process files from highest ID to lowest
    for (int i = files.size() - 1; i >= 0; --i) {
        int best_gap_pos = files[i].pos;
        int best_gap_len = -1;
        // Find the leftmost gap that is large enough
        for (int gap_len = files[i].len; gap_len <= 9; ++gap_len) {
            if (!free_slots[gap_len].empty() && free_slots[gap_len][0] < best_gap_pos) {
                best_gap_pos = free_slots[gap_len][0];
                best_gap_len = gap_len;
            }
        }
        // If a valid gap was found, move the file
        if (best_gap_len != -1) {
            files[i].pos = best_gap_pos;
            // Remove the gap we used
            free_slots[best_gap_len].erase(free_slots[best_gap_len].begin());
            // If there's leftover space in that gap, re-insert it into the correct size list
            int remaining_len = best_gap_len - files[i].len;
            if (remaining_len > 0) {
                int new_pos = best_gap_pos + files[i].len;
                auto &slot_list = free_slots[remaining_len];
                // Keep the slot list sorted so the leftmost gap is always at index 0
                auto it = std::lower_bound(slot_list.begin(), slot_list.end(), new_pos);
                slot_list.insert(it, new_pos);
            }
        }
    }
    // Calculate Checksum
    int64_t checksum = 0;
    for (const auto &file : files) {
        for (int i = 0; i < file.len; ++i) {
            checksum += static_cast<int64_t>(file.id) * (file.pos + i);
        }
    }
    return std::to_string(checksum);
}