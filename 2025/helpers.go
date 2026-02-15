package main

import (
	"fmt"
	"log"
	"os"
	"strings"

	"aoc/2025/solutions"
)

func getInput(file string) string {
	data, err := os.ReadFile(file)
	if err != nil {
		log.Fatal(err)
	}
	return strings.TrimSpace(string(data))
}

var answers = []struct {
	part1 func(string)
	part2 func(string)
	test  string
}{
	1: {solutions.Day1Part2, solutions.Day1Part2, solutions.Day1TEST},
	2: {solutions.Day2Part1, solutions.Day2Part2, solutions.Day2TEST},
	3: {solutions.Day3Part1, solutions.Day3Part2, solutions.Day3TEST},
	4: {solutions.Day4Part1, solutions.Day4Part2, solutions.Day4TEST},
	5: {solutions.Day5Part1, solutions.Day5Part2, solutions.Day5TEST},
}

func Run(day, part int, isTest bool) {
	if day < 0 || day >= len(answers) {
		log.Fatal("\n-> invalid day! <-")
	}
	solution := answers[day]
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
