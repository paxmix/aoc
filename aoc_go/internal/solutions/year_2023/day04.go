package year2023

import (
	"strconv"
	"strings"

	"github.paxmix.aoc/internal/utils"
)

type Day04 struct{}

func init() {
	utils.Registry[4] = Day04{}
}

func (d Day04) Part1(input string) string {
	var total int
	for line := range strings.SplitSeq(input, "\n") {
		if count := winningCount(line); count > 0 {
			total += 1 << (count - 1)
		}
	}
	return strconv.Itoa(total)
}

func (d Day04) Part2(input string) string {
	lines := strings.Split(input, "\n")
	cardCount := len(lines)
	cardCopies := make([]int, cardCount)
	for i := range cardCopies {
		cardCopies[i] = 1
	}
	for i, line := range lines {
		count := winningCount(line)
		for j := i + 1; j < min(i+count+1, cardCount); j++ {
			cardCopies[j] += cardCopies[i]
		}
	}
	var total int
	for _, copies := range cardCopies {
		total += copies
	}
	return strconv.Itoa(total)
}

func winningCount(line string) int {
	// Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
	parts := strings.SplitN(strings.SplitN(line, ":", 2)[1], "|", 2)
	winningNums := strings.Fields(strings.TrimSpace(parts[0]))
	yourNums := strings.Fields(strings.TrimSpace(parts[1]))

	seen := make(map[string]struct{})
	for _, num := range winningNums {
		seen[num] = struct{}{}
	}
	var count int
	for _, num := range yourNums {
		if _, existed := seen[num]; existed {
			count++
		}
	}
	return count
}
