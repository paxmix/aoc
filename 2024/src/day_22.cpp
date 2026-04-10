#include "day_22.hpp"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

using i64 = long long;

namespace {
i64 mix_and_prune(i64 secret, i64 num)
{
    return (secret ^= num) & 0xFFFFFF; // 16777216 = 2^24 -> & ((1<<24)-1)
}
i64 get_next_secret(i64 secret)
{
    secret = mix_and_prune(secret, secret << 6);  // 64 = 2 ^ 6
    secret = mix_and_prune(secret, secret >> 5);  // 32 = 2 ^ 5
    secret = mix_and_prune(secret, secret << 11); // 2048 = 2 ^ 11
    return secret;
}
int encode(int a, int b, int c, int d) { return (a + 9) * 19 * 19 * 19 + (b + 9) * 19 * 19 + (c + 9) * 19 + (d + 9); }
} // namespace

std::string Day22::part_1(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file");
    std::vector<i64> secret_nums;
    std::string line;
    i64 total = 0;
    while (std::getline(file, line)) {
        i64 secret = std::stoll(line);
        for (int i = 0; i < 2000; ++i) {
            secret = get_next_secret(secret);
        }
        total += secret;
    }
    return std::to_string(total);
}
std::string Day22::part_2(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) throw std::runtime_error("failed to open file");
    std::vector<i64> secret_nums;
    std::vector<int> global_scores(130321, 0);    // using base 19 to encode sequence of 4: 19 pow 4
    std::vector<int> last_seen_buyer(130321, -1); // only use the first instance of the sequence for each buyer
    int buyer_id = 0;
    std::string line;
    std::vector<int> prices(2001);
    while (std::getline(file, line)) {
        i64 curr = std::stoll(line);
        prices[0] = curr % 10;
        for (int i = 0; i < 2000; ++i) {
            curr = get_next_secret(curr);
            prices[i + 1] = curr % 10;
        }
        for (int i = 0; i < 2001 - 4; ++i) {
            int a = prices[i + 1] - prices[i];
            int b = prices[i + 2] - prices[i + 1];
            int c = prices[i + 3] - prices[i + 2];
            int d = prices[i + 4] - prices[i + 3];
            int idx = encode(a, b, c, d);
            if (last_seen_buyer[idx] != buyer_id) {
                global_scores[idx] += prices[i + 4];
                last_seen_buyer[idx] = buyer_id;
            }
        }
        ++buyer_id;
    }
    auto max_banana = std::max_element(global_scores.begin(), global_scores.end());
    return std::to_string(*max_banana);
}