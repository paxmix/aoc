package year2023

import (
	"strconv"
	"strings"

	"github.paxmix.aoc/internal/utils"
)

type Day11 struct{}

func init() {
	utils.Registry[11] = Day11{}
}

func (d Day11) Part1(input string) string {
	return solution11(input, 2)
}

func (d Day11) Part2(input string) string {
	return solution11(input, 1_000_000)
}

func solution11(input string, expansionFactor int) string {
	lines := strings.Split(input, "\n")
	rows := len(lines)
	cols := len(lines[0])
	var galaxies [][2]int
	isRowEmpty := make([]bool, rows)
	for i := range isRowEmpty {
		isRowEmpty[i] = true
	}
	isColEmpty := make([]bool, cols)
	for i := range isColEmpty {
		isColEmpty[i] = true
	}

	for r, line := range lines {
		for c := range line {
			if line[c] == '#' {
				galaxies = append(galaxies, [2]int{r, c})
				isRowEmpty[r] = false
				isColEmpty[c] = false
			}
		}
	}

	var total int
	for i := range galaxies {
		for j := i + 1; j < len(galaxies); j++ {
			r1, c1 := galaxies[i][0], galaxies[i][1]
			r2, c2 := galaxies[j][0], galaxies[j][1]
			var dist int
			for r := min(r1, r2); r < max(r1, r2); r++ {
				if isRowEmpty[r] {
					dist += expansionFactor
				} else {
					dist++
				}
			}
			for c := min(c1, c2); c < max(c1, c2); c++ {
				if isColEmpty[c] {
					dist += expansionFactor
				} else {
					dist++
				}
			}
			total += dist
		}
	}

	return strconv.Itoa(total)
}
