#include "day_17.hpp"
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

using i64 = long long;

namespace {
class ChronospatialComputer {
  public:
    ChronospatialComputer(const std::string &filepath)
    {
        std::ifstream file(filepath);
        if (!file.is_open()) throw std::runtime_error("failed to open file: " + filepath);
        std::string line;
        std::vector<int> program;
        std::vector<int> operand;
        std::getline(file, line);
        std::sscanf(line.c_str(), "Register A: %lld", &a_);
        std::getline(file, line);
        std::sscanf(line.c_str(), "Register B: %lld", &b_);
        std::getline(file, line);
        std::sscanf(line.c_str(), "Register C: %lld", &c_);
        std::getline(file, line);
        std::getline(file, line);
        for (char c : line) {
            if (std::isdigit(c)) program_.push_back(c - '0');
        }
    }

    i64 get_combo_value(int operand) const
    {
        if (operand >= 0 && operand <= 3) return operand;
        if (operand == 4) return a_;
        if (operand == 5) return b_;
        if (operand == 6) return c_;
        return 0;
    }
    void run() { execute<false>(); }
    std::string get_output() const
    {
        std::string out;
        for (std::size_t i = 0; i < output_.size(); ++i) {
            out += output_[i] + '0';
            if (i != output_.size() - 1) out += ',';
        }
        return out;
    }

    int program_len() const { return program_.size(); }
    i64 find_a(i64 current_a, int target_idx)
    {
        // Base case: We've matched the whole program string
        if (target_idx < 0) return current_a;

        // Try all 8 possible values for the current 3-bit chunk
        for (int i = 0; i < 8; ++i) {
            i64 next_a = (current_a << 3) | i;
            if (get_first_output(next_a) == program_[target_idx]) {
                i64 final_a = find_a(next_a, target_idx - 1);
                if (final_a != -1) return final_a;
            }
        }
        return -1;
    }

  private:
    i64 a_, b_, c_;
    std::vector<int> program_;
    std::vector<int> output_;

    int get_first_output(i64 test_a) { return execute<true>(test_a); }
    template <bool EARLY_EXIT>
    int execute(i64 test_a = -1)
    {
        i64 a = (test_a == -1) ? a_ : test_a;
        i64 b = (test_a == -1) ? b_ : 0;
        i64 c = (test_a == -1) ? c_ : 0;
        size_t ip = 0;

        while (ip < program_.size()) {
            int opcode = program_[ip];
            int operand = program_[ip + 1];
            i64 combo = operand == 4 ? a : operand == 5 ? b : operand == 6 ? c : operand;

            switch (opcode) {
            case 0: {
                a >>= combo;
            } break;
            case 1: {
                b ^= operand;
            } break;
            case 2: {
                b = combo % 8;
            } break;
            case 3: {
                if (a != 0) {
                    ip = operand;
                    continue;
                }
            } break;
            case 4: {
                b ^= c;
            } break;
            case 5: {
                if constexpr (EARLY_EXIT) return static_cast<int>(combo % 8); // get_first_output path
                output_.push_back(combo % 8);                                 // run() path
            } break;
            case 6: {
                b = a >> combo;
            } break;
            case 7: {
                c = a >> combo;
            } break;
            }
            ip += 2;
        }
        return -1;
    }
};
} // namespace

std::string Day17::part_1(const std::string &filepath)
{

    ChronospatialComputer cc{filepath};
    cc.run();
    return cc.get_output();
}
std::string Day17::part_2(const std::string &filepath)
{
    ChronospatialComputer cc{filepath};
    return std::to_string(cc.find_a(0, cc.program_len() - 1));
}