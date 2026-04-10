#include "day_12.hpp"
#include <fstream>
#include <sstream>

// Cheese: compare the area of each region to the area to the sum of the numbers
// of boxes and a specific area of one box (with me 9(full box) is already
// good, but someone said they have to use 8)
std::string Day12::part_1(std::string filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error{"Failed to open file: " + filepath};
    }
    int total = 0;
    std::string line;
    while (std::getline(file, line)) {
        int a, b;
        int n1, n2, n3, n4, n5, n6;
        std::stringstream ss(line);
        char x;
        if (ss >> a >> x >> b >> x >> n1 >> n2 >> n3 >> n4 >> n5 >> n6) {
            int product = a * b;
            int sum = n1 + n2 + n3 + n4 + n5 + n6;
            total += (product >= (sum * 9));
        }
    }
    return std::to_string(total);
}

std::string Day12::part_2(std::string filepath) { return ""; }
