// Package utils stores helper functions for installing and solving AOC puzzles
package utils

import (
	"fmt"
	"io"
	"net/http"
	"os"
	"path/filepath"
	"strings"
	"sync"
	"time"
)

const (
	PuzzleDir = "puzzles"
	NumDays   = 25
)

func GetPuzzles(year int) {
	folder := filepath.Join(PuzzleDir, fmt.Sprint(year))

	if err := os.MkdirAll(folder, 0o755); err != nil {
		panic(fmt.Sprintf("Failed to create directory: %v", err))
	}

	client := &http.Client{}
	var wg sync.WaitGroup

	for day := 1; day <= NumDays; day++ {
		wg.Add(1) // Increment the counter for each goroutine

		// Launch concurrent worker
		go func(d int) {
			defer wg.Done() // Decrement counter when finished

			fmt.Printf("Starting day %d...\n", d)

			input, err := fetchInput(client, year, d)
			if err != nil {
				fmt.Printf("Error fetching day %d: %v\n", d, err)
				return

			}

			filename := filepath.Join(folder, fmt.Sprintf("day_%d.txt", d))
			err = os.WriteFile(filename, input, 0o644)
			if err != nil {
				fmt.Printf("Failed to write day %d: %v\n", d, err)
				return
			}

			fmt.Printf("Finished day %d\n", d)
		}(day) // Pass 'day' as a parameter to avoid closure capture issues
	}

	wg.Wait() // Block until all wg.Done() calls are made
}

func fetchInput(client *http.Client, year, day int) ([]byte, error) {
	url := fmt.Sprintf("https://adventofcode.com/%d/day/%d/input", year, day)
	sessionToken := os.Getenv("AOC_SESSION")
	if sessionToken == "" {
		return nil, fmt.Errorf("AOC_SESSION not set")
	}

	req, _ := http.NewRequest("GET", url, nil)
	req.Header.Set("Cookie", fmt.Sprintf("session=%s", sessionToken))

	resp, err := client.Do(req)
	if err != nil {
		return nil, err
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		return nil, fmt.Errorf("bad status: %s", resp.Status)
	}

	body, err := io.ReadAll(resp.Body)
	return body, err
}

type Solution interface {
	Part1(string) string
	Part2(string) string
}

var Registry = make(map[int]Solution)

func Run(year, day, part int) {
	start := time.Now()

	sol, ok := Registry[day]
	if !ok {
		fmt.Printf("Invalid day %d\n", day)
		return
	}

	filepath := fmt.Sprintf("puzzles/%d/day_%d.txt", year, day)
	data, err := os.ReadFile(filepath)
	if err != nil {
		fmt.Printf("Input file not found: %s\n", filepath)
		return
	}

	input := strings.TrimSpace(string(data))

	var answer string
	switch part {
	case 1:
		answer = sol.Part1(input)
	case 2:
		answer = sol.Part2(input)
	default:
		fmt.Println("Each day only has two parts")
		return
	}

	duration := time.Since(start).Microseconds()
	fmt.Printf("Year %d Day %d part %d answer is %s (took %d μs)\n", year, day, part, answer, duration)
}
