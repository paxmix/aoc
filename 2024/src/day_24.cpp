#include "day_24.hpp"
#include <fstream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using i64 = long long;

namespace {
struct Gate {
    std::string in1_, in2_, op_, out_;
    bool processed = false;
};
} // namespace

std::string Day24::part_1(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
    std::string line;
    std::unordered_map<std::string, int> wires;
    while (std::getline(file, line) && !line.empty()) {
        size_t colon = line.find(':');
        wires[line.substr(0, colon)] = std::stoi(line.substr(colon + 2));
    }
    std::vector<Gate> gates;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string in1, op, in2, arrow, out;
        iss >> in1 >> op >> in2 >> arrow >> out;
        gates.emplace_back(in1, in2, op, out);
    }
    bool changed = true;
    while (changed) {
        changed = false;
        for (auto &gate : gates) {
            if (!gate.processed && wires.contains(gate.in1_) && wires.contains(gate.in2_)) {
                int v1 = wires[gate.in1_];
                int v2 = wires[gate.in2_];
                wires[gate.out_] = gate.op_ == "AND"   ? v1 & v2
                                   : gate.op_ == "OR"  ? v1 | v2
                                   : gate.op_ == "XOR" ? v1 ^ v2
                                                       : 0;
                gate.processed = true;
                changed = true;
            }
        }
    }
    i64 result = 0;
    for (const auto &[name, value] : wires) {
        if (name[0] == 'z' && value == 1) {
            int bit = std::stoi(name.substr(1));
            result |= (1LL << bit);
        }
    }
    return std::to_string(result);
}
std::string Day24::part_2(const std::string &filepath)
{
    std::ifstream file(filepath);
    std::string line;
    std::vector<Gate> gates;

    // Skip initial wire values
    while (std::getline(file, line) && !line.empty()) {
    }
    // Parse Gates
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string in1, op, in2, arrow, out;
        ss >> in1 >> op >> in2 >> arrow >> out;
        gates.emplace_back(in1, in2, op, out);
    }
    std::set<std::string> faulty;
    for (const auto &g : gates) {
        // Rule 1: z-wires must come from XOR (except the last one)
        if (g.out_[0] == 'z' && g.op_ != "XOR" && g.out_ != "z45") {
            faulty.insert(g.out_);
        }
        // Rule 2: Internal XORs must take x/y or output to z
        if (g.op_ == "XOR" && g.out_[0] != 'z' && g.in1_[0] != 'x' && g.in1_[0] != 'y' && g.in2_[0] != 'x' &&
            g.in2_[0] != 'y') {
            faulty.insert(g.out_);
        }
        // Rule 3 & 4: Propagation checks
        if (g.op_ == "XOR" && (g.in1_[0] == 'x' || g.in1_[0] == 'y')) {
            if (g.in1_ != "x00" && g.in1_ != "y00") { // Skip bit 0
                bool foundXor = false;
                for (const auto &other : gates) {
                    if (other.op_ == "XOR" && (other.in1_ == g.out_ || other.in2_ == g.out_)) {
                        foundXor = true;
                        break;
                    }
                }
                if (!foundXor) faulty.insert(g.out_);
            }
        }
        if (g.op_ == "AND" && (g.in1_[0] == 'x' || g.in1_[0] == 'y')) {
            if (g.in1_ != "x00" && g.in1_ != "y00") { // Skip bit 0
                bool foundOr = false;
                for (const auto &other : gates) {
                    if (other.op_ == "OR" && (other.in1_ == g.out_ || other.in2_ == g.out_)) {
                        foundOr = true;
                        break;
                    }
                }
                if (!foundOr) faulty.insert(g.out_);
            }
        }
    }
    // Output results sorted alphabetically
    std::string result;
    for (const auto &name : faulty) {
        result += name + ",";
    }
    if (!result.empty()) result.pop_back(); // Remove trailing comma

    return result;
}