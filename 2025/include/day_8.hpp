#pragma once

#include "helpers.hpp"
class Day8 : public Solution {
  public:
    std::size_t max_union = 1000;
    Day8(std::size_t max_union = 1000) : max_union(max_union) {}

    std::string part_1(std::string filepath) override;
    std::string part_2(std::string filepath) override;
};