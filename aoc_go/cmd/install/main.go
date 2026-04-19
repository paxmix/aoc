package main

import (
	"log"

	"github.com/joho/godotenv"
	"github.paxmix.aoc/internal/utils"
)

func main() {
	// Load .env file
	err := godotenv.Load()
	if err != nil {
		log.Fatal("Error loading .end file")
	}

	year := 2023
	utils.GetPuzzles(year)
}
