package main

import (
	"fmt"
	"io"
	"log"
	"net/http"
	"os"
	"strings"

	day1 "aoc/2025/day_1"
	day2 "aoc/2025/day_2"
	day3 "aoc/2025/day_3"
	day4 "aoc/2025/day_4"
	day5 "aoc/2025/day_5"

	"github.com/joho/godotenv"
)

func FetchData(day int) string {
	err := godotenv.Load()
	if err != nil {
		log.Println("Warning: .env file not found, using environment variables")
	}

	sessionToken := os.Getenv("AOC_SESSION")
	if sessionToken == "" {
		log.Fatal("AOC_SESSION not set in environment")
	}

	url := fmt.Sprintf("https://adventofcode.com/2025/day/%d/input", day)
	req, _ := http.NewRequest("GET", url, nil)
	req.Header.Set("Cookie", fmt.Sprintf("session=%s", sessionToken))

	resp, err := http.DefaultClient.Do(req)
	if err != nil {
		log.Fatalf("Failed to fetch input: %v", err)
	}
	defer func() {
		if closeErr := resp.Body.Close(); closeErr != nil {
			log.Printf("Failed to close response body: %v", closeErr)
		}
	}()

	if resp.StatusCode != http.StatusOK {
		log.Fatalf("Failed to fetch input: status %d", resp.StatusCode)
	}

	body, err := io.ReadAll(resp.Body)
	if err != nil {
		log.Fatalf("Failed to read response: %v", err)
	}

	return strings.TrimSpace(string(body))
}

func getInput(file string) string {
	data, err := os.ReadFile(file)
	if err != nil {
		log.Fatal(err)
	}
	return strings.TrimSpace(string(data))
}

var solutions = []struct {
	Part1 func(string)
	Part2 func(string)
	TEST  string
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
	file := fmt.Sprintf("day_%d/puzzle.txt", day)
	if isTest {
		input = solution.TEST
	} else {
		input = getInput(file)
	}
	switch part {
	case 1:
		solution.Part1(input)
	case 2:
		solution.Part2(input)
	default:
		fmt.Println("Each day only has two parts")
	}
}
