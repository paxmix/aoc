#pragma once
#include <string>

class Solution {
  public:
    virtual ~Solution() = default;

    virtual std::string part_1(const std::string &filepath) = 0;
    virtual std::string part_2(const std::string &filepath) = 0;
};

void run(int day, int part);