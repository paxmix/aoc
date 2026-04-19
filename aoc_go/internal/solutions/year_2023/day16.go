package year2023

import (
	"strconv"
	"strings"

	"github.paxmix.aoc/internal/utils"
)

type Day16 struct{}

func init() {
	utils.Registry[16] = Day16{}
}

func (d Day16) Part1(input string) string {
	lines := strings.Split(input, "\n")
	rows := len(lines)
	cols := len(lines[0])
	grid := make([][]byte, rows)
	for i := range grid {
		grid[i] = []byte(lines[i])
	}
	// Pre-allocate the visited buffer once
	visited := make([][]uint8, rows)
	for i := range visited {
		visited[i] = make([]uint8, cols)
	}
	return strconv.Itoa(getEnergizedCount(grid, visited, beam{r: 0, c: 0, dir: east}))
}

func (d Day16) Part2(input string) string {
	lines := strings.Split(input, "\n")
	rows := len(lines)
	cols := len(lines[0])
	grid := make([][]byte, rows)
	for i := range grid {
		grid[i] = []byte(lines[i])
	}
	var maxEnergized int

	// basically a map[(r,c), dir]bool using & bitwise AND
	visited := make([][]uint8, rows)
	for i := range visited {
		visited[i] = make([]uint8, cols)
	}

	resetVisited := func() {
		for r := range visited {
			for c := range visited[r] {
				visited[r][c] = 0
			}
		}
	}

	check := func(start beam) {
		resetVisited()
		if count := getEnergizedCount(grid, visited, start); count > maxEnergized {
			maxEnergized = count
		}
	}

	for c := range cols {
		check(beam{0, c, south})
		check(beam{rows - 1, c, north})
	}
	for r := range rows {
		check(beam{r, 0, east})
		check(beam{r, cols - 1, east})
	}

	return strconv.Itoa(maxEnergized)
}

func getEnergizedCount(grid [][]byte, visited [][]uint8, start beam) int {
	rows := len(grid)
	cols := len(grid[0])
	// Use a slice as a stack for DFS
	stack := []beam{start}

	var count int

	for len(stack) > 0 {
		b := stack[len(stack)-1]
		stack = stack[:len(stack)-1]

		// Check bounds
		if b.r < 0 || b.r >= rows || b.c < 0 || b.c >= cols {
			continue
		}
		// Map direction to bitmask
		var mask uint8
		switch b.dir {
		case north:
			mask = nMask
		case south:
			mask = sMask
		case east:
			mask = eMask
		case west:
			mask = wMask
		}
		// If this bit is already set, we've been here in this direction
		if visited[b.r][b.c]&mask != 0 {
			continue
		}
		// If this is the first time visiting this tile at all, it's a "new" energized tile
		if visited[b.r][b.c] == 0 {
			count++
		}
		visited[b.r][b.c] |= mask
		// Process Tile Logic
		char := grid[b.r][b.c]
		for _, nextDir := range getNextDirection(char, b.dir) {
			nextBeam := b
			switch nextDir {
			case east:
				nextBeam.c++
			case north:
				nextBeam.r--
			case south:
				nextBeam.r++
			case west:
				nextBeam.c--
			}
			nextBeam.dir = nextDir
			stack = append(stack, nextBeam)
		}
	}
	return count
}

type beam struct {
	r, c int
	dir  direction
}

const (
	nMask uint8 = 1 << iota
	sMask
	eMask
	wMask
)

func getNextDirection(char byte, dir direction) []direction {
	switch char {
	case '/':
		switch dir {
		case east:
			return []direction{north}
		case north:
			return []direction{east}
		case south:
			return []direction{west}
		case west:
			return []direction{south}
		}
	case '\\':
		switch dir {
		case east:
			return []direction{south}
		case north:
			return []direction{west}
		case south:
			return []direction{east}
		case west:
			return []direction{north}
		}
	case '|':
		if dir == east || dir == west {
			return []direction{north, south}
		}
	case '-':
		if dir == north || dir == south {
			return []direction{east, west}
		}
	}
	return []direction{dir}
}
