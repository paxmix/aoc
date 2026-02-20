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

type Solution interface {
	Part1(string) string
	Part2(string) string
}

func Run(day, part int) {
	solution := getSolution(day)
	input := getInput(fmt.Sprintf("puzzles/day_%d.txt", day))
	var output string
	switch part {
	case 1:
		output = solution.Part1(input)
	case 2:
		output = solution.Part2(input)
	default:
		fmt.Println("Each day only has two parts")
		return
	}

	fmt.Printf("Day %d part %d answer: %s", day, part, output)
}

func getSolution(day int) Solution {
	solutions := []Solution{
		sol.Day1{},
		sol.Day2{},
		sol.Day3{},
		sol.Day4{},
		sol.Day5{},
	}

	return solutions[day-1]
}
