package year2023

import (
	"strconv"
	"strings"

	"github.paxmix.aoc/internal/utils"
)

type Day02 struct{}

func init() {
	utils.Registry[2] = Day02{}
}

func (d Day02) Part1(input string) string {
	LIMITS := map[string]int{"red": 12, "green": 13, "blue": 14}
	total := 0
	for line := range strings.SplitSeq(input, "\n") {
		// Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
		isValid := true
		parts := strings.SplitN(line, ":", 2)
		items := strings.FieldsFuncSeq(parts[1], func(c rune) bool {
			return c == ',' || c == ';'
		})

		for item := range items {
			details := strings.SplitN(strings.TrimSpace(item), " ", 2)
			count, _ := strconv.Atoi(details[0])
			color := details[1]
			if limit := LIMITS[color]; count > limit {
				isValid = false
				break
			}
		}

		if isValid {
			id, _ := strconv.Atoi(strings.TrimPrefix(parts[0], "Game "))
			total += id
		}
	}
	return strconv.Itoa(total)
}

func (d Day02) Part2(input string) string {
	var total int
	for line := range strings.SplitSeq(input, "\n") {
		var maxRed, maxGreen, maxBlue int

		items := strings.FieldsFuncSeq(strings.SplitN(line, ":", 2)[1], func(c rune) bool {
			return c == ',' || c == ';'
		})

		for item := range items {
			details := strings.SplitN(strings.TrimSpace(item), " ", 2)
			count, _ := strconv.Atoi(details[0])
			color := details[1]
			switch color {
			case "red":
				maxRed = max(maxRed, count)
			case "green":
				maxGreen = max(maxGreen, count)
			case "blue":
				maxBlue = max(maxBlue, count)
			}

		}
		total += maxRed * maxGreen * maxBlue
	}

	return strconv.Itoa(total)
}
