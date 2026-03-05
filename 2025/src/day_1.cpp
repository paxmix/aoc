#include "day_1.hpp"
#include <fstream>
#include <iostream>
#include <string>

std::string Day1::part_1(std::string file_path)
{
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return "";
    }

    int dial = 50;
    int pwd = 0;
    std::string line;

    while (std::getline(file, line)) {
        std::string dir = line.substr(0, 1);
        std::string num = line.substr(1);
        try {
            int val = std::stoi(num);
            if (dir == "R") {
                dial += val;
            } else if (dir == "L") {
                dial -= val;
            }

            dial = (dial % 100 + 100) % 100;
            if (dial == 0) {
                pwd++;
            }
        } catch (const std::invalid_argument &e) {
            std::cout << "Invalid number\n";
        } catch (const std::out_of_range &e) {
            std::cout << "Number out of range\n";
        }
    }
    file.close();
    return std::to_string(pwd);
}

std::string Day1::part_2(std::string file_path)
{
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return "";
    }
    int dial = 50;
    int pwd = 0;
    std::string line;
    while (std::getline(file, line)) {
        std::string dir = line.substr(0, 1);
        std::string num = line.substr(1);
        try {
            int val = std::stoi(num);

            int base = dial;
            if (dir == "R") {
                dial += val;
            } else if (dir == "L") {
                dial -= val;
            }
            if (dial < 0) {
                pwd -= dial / 100 - 1;
                if (base == 0) {
                    pwd--;
                }
            } else if (dial >= 100) {
                pwd += dial / 100;
            } else if (dial == 0) {
                pwd++;
            }
            dial = (dial % 100 + 100) % 100;
        } catch (const std::invalid_argument &e) {
            std::cout << "Invalid number\n";
        } catch (const std::out_of_range &e) {
            std::cout << "Number out of range\n";
        }
    }
    file.close();
    return std::to_string(pwd);
}
