#include "helpers.hpp"
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
#include <iostream>
#include <memory>
#include <print>

constexpr int NUM_DAYS = 12;

template <typename Day> std::unique_ptr<Solution> create()
{
	return std::make_unique<Day>();
}
using Factory = std::unique_ptr<Solution> (*)();
static constexpr std::array<Factory, NUM_DAYS> factories = {
	&create<Day1>,
	&create<Day2>,
	&create<Day3>,
	&create<Day4>,
	&create<Day5>,
	&create<Day6>,
	&create<Day7>,
	&create<Day8>,
	&create<Day9>,
	&create<Day10>,
	&create<Day11>,
	&create<Day12>,
};

std::unique_ptr<Solution> get_solution(size_t day)
{
	if (day < 1 || day > NUM_DAYS) {
		return nullptr;
	}
	return factories[day - 1]();
}

void run(int day, int part)
{
	auto sol = get_solution(day);
	if (!sol) {
		std::println("Invalid day {}", day);
		return;
	}
	std::string answer = "";
	std::string filepath = std::format(
			"/home/paxmix/Projects/aoc_cpp/2025/puzzles/day_{}.txt", day);
	if (part == 1) {
		answer = sol->part_1(filepath);
	} else if (part == 2) {
		answer = sol->part_2(filepath);
	} else {
		std::cout << "Each day only have two parts\n";
		return;
	}
	if (!answer.empty()) {
		std::println(
				"Year 2025 Day {} Part {} answer is {}", day, part, answer);
	}
}
