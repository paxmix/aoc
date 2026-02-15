package main

import (
	"fmt"
	"log"
	"os"
	"strings"

	day1 "aoc/2025/day_1"
	day2 "aoc/2025/day_2"
	day3 "aoc/2025/day_3"
	day4 "aoc/2025/day_4"
	day5 "aoc/2025/day_5"
)

func getInput(file string) string {
	data, err := os.ReadFile(file)
	if err != nil {
		log.Fatal(err)
	}
	return strings.TrimSpace(string(data))
}

var solutions = []struct {
	part1 func(string)
	part2 func(string)
	test  string
}{
	1: {day1.Part1, day1.Part1, day1.TEST},
	2: {day2.Part2, day2.Part2, day2.TEST},
	3: {day3.Part1, day3.Part2, day3.TEST},
	4: {day4.Part1, day4.Part2, day4.TEST},
	5: {day5.Part1, day5.Part2, day5.TEST},
}

func Run(day, part int, isTest bool) {
	if day < 0 || day >= len(solutions) {
		log.Fatal("\n-> invalid day! <-")
	}
	solution := solutions[day]
	if day == 1 && part == 1 {
		fmt.Println("Day 1 only have part 2")
		part = 2
	}
	var input string
	file := fmt.Sprintf("puzzles/day_%d.txt", day)
	if isTest {
		input = solution.test
	} else {
		input = getInput(file)
	}
	switch part {
	case 1:
		solution.part1(input)
	case 2:
		solution.part2(input)
	default:
		fmt.Println("Each day only has two parts")
	}
}
