package main

import (
	"bytes"
	"errors"
	"fmt"
	"io"
	"log"
	"net/http"
	"os"
	"strings"
	"time"

	sol "aoc/2025/solutions"

	"github.com/joho/godotenv"
)

const totalDay int = 12

func DownloadPuzzles() {
	err := godotenv.Load()
	if err != nil {
		log.Println("Warning: .env file not found, using environment variables")
	}
	sessionToken := os.Getenv("AOC_SESSION")
	if sessionToken == "" {
		log.Fatal("AOC_SESSION not set in environment")
	}
	client := &http.Client{
		Timeout: 15 * time.Second,
	}
	err = os.MkdirAll("puzzles", 0o755)
	if err != nil {
		log.Fatal(err)
	}
	for day := 1; day <= totalDay; day++ {
		err := fetchPuzzle(day, sessionToken, client)
		if err != nil {
			log.Printf("error fetching day %d puzzle: %s", day, err)
			continue
		}
	}
}

var ErrFailToFetchInput error = errors.New("failed to fetch input")

func fetchPuzzle(day int, cookie string, client *http.Client) error {
	url := fmt.Sprintf("https://adventofcode.com/2025/day/%d/input", day)
	req, err := http.NewRequest("GET", url, nil)
	if err != nil {
		return err
	}
	req.Header.Set("Cookie", fmt.Sprintf("session=%s", cookie))

	resp, err := client.Do(req)
	if err != nil {
		return err
	}
	if resp.StatusCode != http.StatusOK {
		return ErrFailToFetchInput
	}
	body, err := io.ReadAll(resp.Body)
	if err != nil {
		return err
	}
	if closeErr := resp.Body.Close(); closeErr != nil {
		return closeErr
	}

	path := fmt.Sprintf("puzzles/day_%d.txt", day)
	err = os.WriteFile(path, bytes.TrimRight(body, "\n"), 0o644)
	if err != nil {
		return err
	}
	return nil
}

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
	6: {sol.Day6Part1, sol.Day6Part2, sol.Day6TEST},
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
