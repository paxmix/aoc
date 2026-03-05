#include "day_2.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>

using u64 = std::uint64_t;

bool is_valid_factor(u64 id, size_t factor, size_t id_len);
bool is_valid(u64 id);
u64 pow_10(size_t factor);
size_t int_len(u64 num);

template <typename lambda>
std::string solution(lambda is_invalid, std::string filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return "";
    }
    u64 sum = 0;
    std::string pair;
    while (std::getline(file, pair, ',')) {
        size_t pos = pair.find('-');
        if (pos == std::string::npos) {
            std::cerr << "Invalid format: " << pair << '\n';
            continue;
        }
        try {
            u64 low = stoull(pair.substr(0, pos));
            u64 high = stoull(pair.substr(pos + 1));
            for (u64 id = low; id <= high; ++id) {
                if (is_invalid(id)) sum += id;
            }
        } catch (const std::exception &e) {
            std::cerr << "Parse error in \"" << pair << "\":" << e.what()
                      << '\n';
            continue;
        }
    }
    return std::to_string(sum);
}

std::string Day2::part_1(std::string filepath)
{
    return solution(
        [](u64 id) {
            size_t length = int_len(id);
            return length % 2 == 0 && !is_valid_factor(id, 2, length);
        },
        filepath);
}

std::string Day2::part_2(std::string filepath)
{
    return solution([](u64 id) { return !is_valid(id); }, filepath);
}

bool is_valid_factor(u64 id, size_t factor, size_t id_len)
{
    u64 factor_10 = pow_10(id_len / factor);
    u64 base = id % factor_10;
    while (id > 0) {
        if (base != (id % factor_10)) {
            return true;
        }
        id /= factor_10;
    }
    return false;
}

bool is_valid(u64 id)
{
    size_t length = int_len(id);
    for (size_t factor = 2; factor <= length; ++factor) {
        if (length % factor == 0 && !is_valid_factor(id, factor, length)) {
            return false;
        }
    }
    return true;
}

u64 pow_10(size_t factor)
{
    u64 result = 1;
    while (factor--) {
        result *= 10;
    }
    return result;
}

size_t int_len(u64 num)
{
    size_t length = 1;
    while (num /= 10) {
        length++;
    }
    return length;
}
