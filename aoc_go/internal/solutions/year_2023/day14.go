package year2023

import (
	"strconv"
	"strings"

	"github.paxmix.aoc/internal/utils"
)

type Day14 struct{}

func init() {
	utils.Registry[14] = Day14{}
}

func (d Day14) Part1(input string) string {
	gridStr := strings.Split(input, "\n")
	rows := len(gridStr)
	cols := len(gridStr[0])

	grid := make([][]byte, rows)
	for i := range gridStr {
		grid[i] = []byte(gridStr[i])
	}

	for c := range cols {
		var nextAvailableRow int // Track the row that the next 'O' land

		for r := range rows {
			switch grid[r][c] {
			case 'O':
				// the if check is for the initialized nextAvailableRow cell already a 'O'
				if r != nextAvailableRow {
					grid[nextAvailableRow][c] = 'O'
					grid[r][c] = '.'
				}
				nextAvailableRow++ // After switch, must move below current available row
			case '#':
				nextAvailableRow = r + 1 // Meet a wall, must move below this row
			}
		}
	}

	var total int
	for i := range grid {
		total += utils.SliceCount(grid[i], 'O') * (rows - i)
	}
	return strconv.Itoa(total)
}

func (d Day14) Part2(input string) string {
	rows := strings.Split(strings.TrimSpace(string(input)), "\n")
	grid := make([][]byte, len(rows))
	for i, row := range rows {
		grid[i] = []byte(row)
	}

	seen := make(map[string]int)
	var history [][][]byte

	const totalCycles int = 1_000_000_000
	for i := range totalCycles {
		state := gridToString(grid)
		if firstSeen, exists := seen[state]; exists {
			// Cycle detected!
			loopLen := i - firstSeen
			remaining := (totalCycles - firstSeen) % loopLen
			grid = history[firstSeen+remaining]
			break
		}
		seen[state] = i
		// Copy grid to history
		history = append(history, copyGrid(grid))
		// Perform full spin cycle
		grid = spinCycle(grid)
	}

	return strconv.Itoa(calculateLoad(grid))
}

// spinCycle performs North, West, South, East tilts
func spinCycle(grid [][]byte) [][]byte {
	for range 4 {
		grid = tiltNorth(grid)
		grid = rotateClockwise(grid)
	}
	return grid
}

func tiltNorth(grid [][]byte) [][]byte {
	rows := len(grid)
	cols := len(grid[0])
	for c := range cols {
		for r := range rows {
			if grid[r][c] == 'O' {
				currR := r
				for currR > 0 && grid[currR-1][c] == '.' {
					grid[currR-1][c] = 'O'
					grid[currR][c] = '.'
					currR--
				}
			}
		}
	}
	return grid
}

func rotateClockwise(grid [][]byte) [][]byte {
	rows := len(grid)
	cols := len(grid[0])
	newGrid := make([][]byte, cols)
	for i := range newGrid {
		newGrid[i] = make([]byte, rows)
	}
	for r := range rows {
		for c := range cols {
			newGrid[c][rows-1-r] = grid[r][c]
		}
	}
	return newGrid
}

func calculateLoad(grid [][]byte) int {
	var load int
	rows := len(grid)
	for r, row := range grid {
		for _, char := range row {
			if char == 'O' {
				load += rows - r
			}
		}
	}
	return load
}

func gridToString(grid [][]byte) string {
	var sb strings.Builder
	for _, row := range grid {
		sb.WriteString(string(row))
	}
	return sb.String()
}

func copyGrid(grid [][]byte) [][]byte {
	newGrid := make([][]byte, len(grid))
	for i := range grid {
		newGrid[i] = make([]byte, len(grid[i]))
		copy(newGrid[i], grid[i])
	}
	return newGrid
}
