package main

import (
	"fmt"
	"log"
	"os"
	"strings"

	sol "aoc/2025/solutions"
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
	1: {sol.Day1Part2, sol.Day1Part2, sol.Day1TEST},
	2: {sol.Day2Part1, sol.Day2Part2, sol.Day2TEST},
	3: {sol.Day3Part1, sol.Day3Part2, sol.Day3TEST},
	4: {sol.Day4Part1, sol.Day4Part2, sol.Day4TEST},
	5: {sol.Day5Part1, sol.Day5Part2, sol.Day5TEST},
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
