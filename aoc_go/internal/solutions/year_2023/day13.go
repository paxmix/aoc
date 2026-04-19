package year2023

import (
	"strconv"
	"strings"

	"github.paxmix.aoc/internal/utils"
)

type Day13 struct{}

func init() {
	utils.Registry[13] = Day13{}
}

func (d Day13) Part1(input string) string {
	return solution13(input, 0)
}

func (d Day13) Part2(input string) string {
	return solution13(input, 1)
}

func solution13(input string, targetDiff int) string {
	var total int
	for pattern := range strings.SplitSeq(input, "\n\n") {
		grid := strings.Split(pattern, "\n")
		// Part 1 want a perfect reflection
		// Part 2 want reflection with exactly 1 diff
		if idx, ok := findReflection(grid, targetDiff); ok {
			total += 100 * idx
		} else if idx, ok := findReflection(transpose(grid), targetDiff); ok {
			total += idx
		}
	}
	return strconv.Itoa(total)
}

func findReflection(grid []string, targetDiff int) (int, bool) {
	for i := 1; i < len(grid); i++ {
		var diff int
		// Split grid rows at index i
		// traverse above and below to check for reflection, above goes in reverse
		// essentially a simple zip for grid[:i].rev() and grid[i:]
		for above, below := i-1, i; above >= 0 && below < len(grid); above, below = above-1, below+1 {
			diff += stringDiff(grid[above], grid[below])
			if diff > targetDiff {
				break
			}
		}
		if diff == targetDiff {
			return i, true
		}
	}
	return 0, false
}

func stringDiff(a, b string) int {
	var diff int
	for i := range a {
		if a[i] != b[i] {
			diff++
		}
	}
	return diff
}

func transpose(grid []string) []string {
	rows := len(grid)
	cols := len(grid[0])
	result := make([]string, cols)
	for c := range cols {
		rowBytes := make([]byte, rows)
		for r := range rows {
			rowBytes[r] = grid[r][c]
		}
		result[c] = string(rowBytes)
	}
	return result
}
