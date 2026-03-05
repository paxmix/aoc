#include "day_1.hpp"
#include "day_10.hpp"
#include "day_11.hpp"
#include "day_12.hpp"
#include "day_2.hpp"
#include "day_3.hpp"
#include "day_4.hpp"
#include "day_5.hpp"
#include "day_6.hpp"
#include "day_7.hpp"
#include "day_8.hpp"
#include "day_9.hpp"
#include <catch2/catch_test_macros.hpp>

std::string test_file(std::string day)
{
    return std::format(
        "/home/paxmix/Projects/aoc_cpp/2025/puzzles/tests/day_{}.txt", day);
}

TEST_CASE("Day 1")
{
    std::string filepath = test_file("1");
    const auto DAY1 = std::make_unique<Day1>();
    REQUIRE(DAY1->part_1(filepath) == "3");
    REQUIRE(DAY1->part_2(filepath) == "6");
}
TEST_CASE("Day 2")
{
    std::string filepath = test_file("2");
    const auto DAY2 = std::make_unique<Day2>();
    REQUIRE(DAY2->part_1(filepath) == "1227775554");
    REQUIRE(DAY2->part_2(filepath) == "4174379265");
}
TEST_CASE("Day 3")
{
    std::string filepath = test_file("3");
    const auto DAY3 = std::make_unique<Day3>();
    REQUIRE(DAY3->part_1(filepath) == "357");
    REQUIRE(DAY3->part_2(filepath) == "3121910778619");
}
TEST_CASE("Day 4")
{
    std::string filepath = test_file("4");
    const auto DAY4 = std::make_unique<Day4>();
    REQUIRE(DAY4->part_1(filepath) == "13");
    REQUIRE(DAY4->part_2(filepath) == "43");
}
TEST_CASE("Day 5")
{
    std::string filepath = test_file("5");
    const auto DAY5 = std::make_unique<Day5>();
    REQUIRE(DAY5->part_1(filepath) == "3");
    REQUIRE(DAY5->part_2(filepath) == "14");
}
TEST_CASE("Day 6")
{
    std::string filepath = test_file("6");
    const auto DAY6 = std::make_unique<Day6>();
    REQUIRE(DAY6->part_1(filepath) == "4277556");
    REQUIRE(DAY6->part_2(filepath) == "3263827");
}
TEST_CASE("Day 7")
{
    std::string filepath = test_file("7");
    const auto DAY7 = std::make_unique<Day7>();
    REQUIRE(DAY7->part_1(filepath) == "21");
    REQUIRE(DAY7->part_2(filepath) == "40");
}
TEST_CASE("Day 8")
{
    std::string filepath = test_file("8");
    const auto DAY8 = std::make_unique<Day8>(10);
    REQUIRE(DAY8->part_1(filepath) == "40");
    REQUIRE(DAY8->part_2(filepath) == "25272");
}
TEST_CASE("Day 9")
{
    std::string filepath = test_file("9");
    const auto DAY9 = std::make_unique<Day9>();
    REQUIRE(DAY9->part_1(filepath) == "50");
    REQUIRE(DAY9->part_2(filepath) == "24");
}
TEST_CASE("Day 10")
{
    std::string filepath = test_file("10");
    const auto DAY10 = std::make_unique<Day10>();
    REQUIRE(DAY10->part_1(filepath) == "7");
    REQUIRE(DAY10->part_2(filepath) == "33");
}
TEST_CASE("Day 11")
{
    std::string filepath = test_file("11_1");
    const auto DAY = std::make_unique<Day11>();
    REQUIRE(DAY->part_1(filepath) == "5");

    filepath = test_file("11_2");
    REQUIRE(DAY->part_2(filepath) == "2");
}
TEST_CASE("Day 12")
{
    std::string filepath = test_file("12");
    const auto DAY = std::make_unique<Day12>();
    REQUIRE(DAY->part_1(filepath) == "2");
}