package year2023

import (
	"strconv"
	"strings"
	"unicode"

	"github.paxmix.aoc/internal/utils"
)

type Day03 struct{}

func init() {
	utils.Registry[3] = Day03{}
}

func (d Day03) Part1(input string) string {
	lines := strings.Split(input, "\n")
	rows := len(lines)
	cols := len(lines[0])
	var sum int
	for r := range rows {
		var c int
		for c < cols {
			if unicode.IsDigit(rune(lines[r][c])) {
				start := c
				var numStr strings.Builder
				for c < cols && unicode.IsDigit(rune(lines[r][c])) {
					numStr.WriteByte(lines[r][c])
					c++
				}
				end := c - 1
				// check surrounding neighbors for a symbol
				if hasSymbolNeighbor(lines, r, start, end) {
					val, _ := strconv.Atoi(numStr.String())
					sum += val
				}
			} else {
				c++
			}
		}
	}
	return strconv.Itoa(sum)
}

func (d Day03) Part2(input string) string {
	lines := strings.Split(input, "\n")
	var numberList []int
	coordToNumIdx := make(map[Point]int)

	for r, line := range lines {
		for c := 0; c < len(line); {
			if unicode.IsDigit(rune(line[c])) {
				start := c
				for c < len(line) && unicode.IsDigit(rune(line[c])) {
					c++
				}
				val, _ := strconv.Atoi(line[start:c])
				idx := len(numberList)
				numberList = append(numberList, val)
				for i := start; i < c; i++ {
					coordToNumIdx[Point{r, i}] = idx
				}
			} else {
				c++
			}
		}
	}

	var totalRatio int
	for r, line := range lines {
		for c, char := range line {
			if char == '*' {
				adjacentIndices := make(map[int]bool)

				for dr := -1; dr <= 1; dr++ {
					for dc := -1; dc <= 1; dc++ {
						if dr == 0 && dc == 0 {
							continue
						}
						if idx, ok := coordToNumIdx[Point{r + dr, c + dc}]; ok {
							adjacentIndices[idx] = true
						}
					}
				}

				if len(adjacentIndices) == 2 {
					ratio := 1
					for idx := range adjacentIndices {
						ratio *= numberList[idx]
					}
					totalRatio += ratio
				}
			}
		}
	}
	return strconv.Itoa(totalRatio)
}

func hasSymbolNeighbor(lines []string, r, start, end int) bool {
	rows := len(lines)
	cols := len(lines[0])
	for i := r - 1; i <= r+1; i++ {
		if i < 0 || i >= rows {
			continue
		}
		for j := start - 1; j <= end+1; j++ {
			if j < 0 || j >= cols {
				continue
			}
			b := lines[i][j]
			if !unicode.IsDigit(rune(b)) && b != '.' {
				return true
			}
		}
	}
	return false
}

type Point struct {
	x, y int
}
