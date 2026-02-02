// Package day4: You ride the escalator down to the printing department. They're clearly getting ready for Christmas; they have lots of large rolls of paper everywhere, and there's even a massive printer in the corner (to handle the really big print jobs).
// Decorating here will be easy: they can make their own decorations. What you really need is a way to get further into the North Pole base while the elevators are offline.
// "Actually, maybe we can help with that," one of the Elves replies when you ask for help. "We're pretty sure there's a cafeteria on the other side of the back wall. If we could break through the wall, you'd be able to keep moving. It's too bad all of our forklifts are so busy moving those big rolls of paper around."
// If you can optimize the work the forklifts are doing, maybe they would have time to spare to break through the wall.
// The rolls of paper (@) are arranged on a large grid; the Elves even have a helpful diagram (your puzzle input) indicating where everything is located.
package day4

import (
	"fmt"
	"strings"
)

const (
	TEST = `..@@.@@@@.
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

func Part1(input string) {
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

func Part2(input string) {
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
