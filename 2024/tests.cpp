#include "day_1.hpp"
#include "day_10.hpp"
#include "day_11.hpp"
#include "day_12.hpp"
#include "day_13.hpp"
#include "day_14.hpp"
#include "day_15.hpp"
#include "day_16.hpp"
#include "day_17.hpp"
#include "day_18.hpp"
#include "day_19.hpp"
#include "day_2.hpp"
#include "day_20.hpp"
#include "day_21.hpp"
#include "day_22.hpp"
#include "day_23.hpp"
#include "day_24.hpp"
#include "day_25.hpp"
#include "day_3.hpp"
#include "day_4.hpp"
#include "day_5.hpp"
#include "day_6.hpp"
#include "day_7.hpp"
#include "day_8.hpp"
#include "day_9.hpp"
#include <catch2/catch_test_macros.hpp>

std::string test_file(std::string day) { return std::format("puzzles/tests/day_{}.txt", day); }

TEST_CASE("Day 1")
{
    std::string filepath = test_file("1");
    const auto DAY1 = std::make_unique<Day1>();
    REQUIRE(DAY1->part_1(filepath) == "11");
    REQUIRE(DAY1->part_2(filepath) == "31");
}
TEST_CASE("Day 2")
{
    std::string filepath = test_file("2");
    const auto DAY2 = std::make_unique<Day2>();
    REQUIRE(DAY2->part_1(filepath) == "2");
    REQUIRE(DAY2->part_2(filepath) == "4");
}
TEST_CASE("Day 3")
{
    std::string filepath = test_file("3_1");
    const auto DAY3 = std::make_unique<Day3>();
    REQUIRE(DAY3->part_1(filepath) == "161");
    filepath = test_file("3_2");
    REQUIRE(DAY3->part_2(filepath) == "48");
}
TEST_CASE("Day 4")
{
    std::string filepath = test_file("4_1");
    const auto DAY4 = std::make_unique<Day4>();
    REQUIRE(DAY4->part_1(filepath) == "18");
    filepath = test_file("4_2");
    REQUIRE(DAY4->part_2(filepath) == "9");
}
TEST_CASE("Day 5")
{
    std::string filepath = test_file("5");
    const auto DAY5 = std::make_unique<Day5>();
    REQUIRE(DAY5->part_1(filepath) == "143");
    REQUIRE(DAY5->part_2(filepath) == "123");
}
TEST_CASE("Day 6")
{
    std::string filepath = test_file("6");
    const auto DAY6 = std::make_unique<Day6>();
    REQUIRE(DAY6->part_1(filepath) == "41");
    REQUIRE(DAY6->part_2(filepath) == "6");
}
TEST_CASE("Day 7")
{
    std::string filepath = test_file("7");
    const auto DAY7 = std::make_unique<Day7>();
    REQUIRE(DAY7->part_1(filepath) == "3749");
    REQUIRE(DAY7->part_2(filepath) == "11387");
}
TEST_CASE("Day 8")
{
    std::string filepath = test_file("8");
    const auto DAY8 = std::make_unique<Day8>();
    REQUIRE(DAY8->part_1(filepath) == "14");
    REQUIRE(DAY8->part_2(filepath) == "34");
}
TEST_CASE("Day 9")
{
    std::string filepath = test_file("9");
    const auto DAY9 = std::make_unique<Day9>();
    REQUIRE(DAY9->part_1(filepath) == "1928");
    REQUIRE(DAY9->part_2(filepath) == "2858");
}
TEST_CASE("Day 10")
{
    std::string filepath = test_file("10");
    const auto DAY10 = std::make_unique<Day10>();
    REQUIRE(DAY10->part_1(filepath) == "36");
    REQUIRE(DAY10->part_2(filepath) == "81");
}
TEST_CASE("Day 11")
{
    std::string filepath = test_file("11");
    const auto DAY11 = std::make_unique<Day11>();
    REQUIRE(DAY11->part_1(filepath) == "55312");
}
TEST_CASE("Day 12")
{
    std::string filepath = test_file("12");
    const auto DAY12 = std::make_unique<Day12>();
    REQUIRE(DAY12->part_1(filepath) == "1930");
    REQUIRE(DAY12->part_2(filepath) == "1206");
}
TEST_CASE("Day 13")
{
    std::string filepath = test_file("13");
    const auto DAY13 = std::make_unique<Day13>();
    REQUIRE(DAY13->part_1(filepath) == "480");
}
TEST_CASE("Day 14")
{
    std::string filepath = test_file("14");
    const auto DAY14 = std::make_unique<Day14>();
    REQUIRE(DAY14->part_1(filepath) == "12");
}
TEST_CASE("Day 15")
{
    std::string filepath = test_file("15");
    const auto DAY15 = std::make_unique<Day15>();
    REQUIRE(DAY15->part_1(filepath) == "10092");
}
TEST_CASE("Day 16")
{
    std::string filepath = test_file("16");
    const auto DAY16 = std::make_unique<Day16>();
    REQUIRE(DAY16->part_1(filepath) == "7036");
    REQUIRE(DAY16->part_2(filepath) == "45");
}
TEST_CASE("Day 17")
{
    std::string filepath = test_file("17_1");
    const auto DAY17 = std::make_unique<Day17>();
    REQUIRE(DAY17->part_1(filepath) == "4,6,3,5,6,3,5,2,1,0");
    filepath = test_file("17_2");
    REQUIRE(DAY17->part_2(filepath) == "117440");
}
TEST_CASE("Day 18")
{
    std::string filepath = test_file("18");
    const auto DAY18 = std::make_unique<Day18>();
    REQUIRE(DAY18->part_1(filepath) == "22");
    REQUIRE(DAY18->part_2(filepath) == "6,1");
}
TEST_CASE("Day 19")
{
    std::string filepath = test_file("19");
    const auto DAY19 = std::make_unique<Day19>();
    REQUIRE(DAY19->part_1(filepath) == "6");
    REQUIRE(DAY19->part_2(filepath) == "16");
}
TEST_CASE("Day 20")
{
    std::string filepath = test_file("20");
    const auto DAY20 = std::make_unique<Day20>();
    REQUIRE(DAY20->part_1(filepath) == "44");
    REQUIRE(DAY20->part_2(filepath) == "285");
}
TEST_CASE("Day 21")
{
    std::string filepath = test_file("21");
    const auto DAY21 = std::make_unique<Day21>();
    REQUIRE(DAY21->part_1(filepath) == "126384");
}
TEST_CASE("Day 22")
{
    std::string filepath = test_file("22_1");
    const auto DAY22 = std::make_unique<Day22>();
    REQUIRE(DAY22->part_1(filepath) == "37327623");
    filepath = test_file("22_2");
    REQUIRE(DAY22->part_2(filepath) == "23");
}
TEST_CASE("Day 23")
{
    std::string filepath = test_file("23");
    const auto DAY23 = std::make_unique<Day23>();
    REQUIRE(DAY23->part_1(filepath) == "7");
    REQUIRE(DAY23->part_2(filepath) == "co,de,ka,ta");
}
TEST_CASE("Day 24")
{
    std::string filepath = test_file("24_1");
    const auto DAY24 = std::make_unique<Day24>();
    REQUIRE(DAY24->part_1(filepath) == "2024");
    filepath = test_file("24_2");
    REQUIRE(DAY24->part_2(filepath) == "z00,z01,z02,z03,z04,z05");
}
TEST_CASE("Day 25")
{
    std::string filepath = test_file("25");
    const auto DAY25 = std::make_unique<Day25>();
    REQUIRE(DAY25->part_1(filepath) == "3");
}