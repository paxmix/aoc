package solutions

import (
	"fmt"
	"strings"
)

const (
	Day4TEST = `..@@.@@@@.
@@@.@.@.@@
@@@@@.@.@@
@.@@@@..@.
@@.@@@@.@@
.@@@@@@@.@
.@.@.@.@@@
@.@@@.@@@@
.@@@@@@@@.
@.@.@@@.@.`
)

var dirs = [8][2]int{
	{-1, -1},
	{-1, 0},
	{-1, 1},
	{0, -1},
	{0, 1},
	{1, -1},
	{1, 0},
	{1, 1},
}

func Day4Part1(input string) {
	grid := getGrid(input)

	var accessibleRolls int

	for i := range grid {
		for j := range grid[i] {
			if grid[i][j] == '@' && neighbors(grid, i, j) < 4 {
				fmt.Printf("rolls at row %d, column %d is Accessible\n", i+1, j+1)
				accessibleRolls++
			}
		}
	}

	fmt.Printf("There are %d rolls of paper that can be accessed by a forklift", accessibleRolls)
}

func Day4Part2(input string) {
	grid := getGrid(input)
	var sum int

	for {
		var accessibleRolls int
		for i := range grid {
			for j := range grid[i] {
				if grid[i][j] == '@' && neighbors(grid, i, j) < 4 {
					fmt.Printf("rolls at row %d, column %d is Accessible\n", i+1, j+1)
					grid[i][j] = '.'
					accessibleRolls++
				}
			}
		}
		if accessibleRolls == 0 {
			break
		}
		sum += accessibleRolls
	}

	fmt.Printf("There are %d rolls of paper that can be accessed by a forklift", sum)
}

func neighbors(grid [][]byte, row, col int) int {
	var count int

	for _, dir := range dirs {
		r := row + dir[0]
		c := col + dir[1]

		if r >= 0 && r < len(grid) &&
			c >= 0 && c < len(grid[r]) &&
			grid[r][c] == '@' {
			count++
		}
	}

	return count
}

func getGrid(input string) [][]byte {
	lines := strings.Split(input, "\n")
	grid := make([][]byte, len(lines))
	for i, line := range lines {
		grid[i] = []byte(line)
	}
	return grid
}
