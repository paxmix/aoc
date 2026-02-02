// Package helper store helpers function like FetchData and some repetitive functions
package helper

import (
	"fmt"
	"io"
	"log"
	"net/http"
	"os"

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

	return string(body)
}
