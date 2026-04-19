package year2023

import (
	"strconv"
	"strings"

	"github.paxmix.aoc/internal/utils"
)

type Day10 struct{}

func init() {
	utils.Registry[10] = Day10{}
}

func (d Day10) Part1(input string) string {
	lines := strings.Split(input, "\n")

	curr := getStartPipe(lines)
	var step int
	for {
		switch curr.dir {
		case east:
			curr.col++
		case north:
			curr.row--
		case south:
			curr.row++
		case west:
			curr.col--
		}

		step++
		pipe := lines[curr.row][curr.col]
		if pipe == 'S' {
			break
		}
		curr.changeDir(pipe)
	}
	return strconv.Itoa(step / 2)
}

func (d Day10) Part2(input string) string {
	lines := strings.Split(input, "\n")
	curr := getStartPipe(lines)
	var boundaryPoints int
	var vertices [][2]int

	vertices = append(vertices, [2]int{curr.row, curr.col})
	for {
		switch curr.dir {
		case east:
			curr.col++
		case north:
			curr.row--
		case south:
			curr.row++
		case west:
			curr.col--
		}

		boundaryPoints++
		vertices = append(vertices, [2]int{curr.row, curr.col})

		pipe := lines[curr.row][curr.col]
		if pipe == 'S' {
			break
		}
		curr.changeDir(pipe)
	}

	// Shoelace Formula to calculate area
	var area int
	for i := range len(vertices) - 1 {
		x1, y1 := vertices[i][0], vertices[i][1]
		x2, y2 := vertices[i+1][0], vertices[i+1][1]
		area += x1*y2 - x2*y1
	}
	if area < 0 {
		area = -area
	}
	area /= 2

	// Pick's Theorem for Interior Points
	// area = interior_points + boundary_points/2 - 1;
	return strconv.Itoa(area - boundaryPoints/2 + 1)
}

type coor struct {
	row int
	col int
	dir direction
}
type direction int

const (
	north direction = iota
	east
	south
	west
)

func (c *coor) changeDir(pipe byte) {
	switch {
	case pipe == '|' || pipe == '-':
		return
	case pipe == 'L' && c.dir == south:
		c.dir = east
	case pipe == 'L' && c.dir == west:
		c.dir = north
	case pipe == 'J' && c.dir == south:
		c.dir = west
	case pipe == 'J' && c.dir == east:
		c.dir = north
	case pipe == '7' && c.dir == north:
		c.dir = west
	case pipe == '7' && c.dir == east:
		c.dir = south
	case pipe == 'F' && c.dir == west:
		c.dir = south
	case pipe == 'F' && c.dir == north:
		c.dir = east
	}
}

func getStartPipe(lines []string) coor {
	var r, c int
	var dir direction

coorLoop:
	for i := range lines {
		for j := range lines[i] {
			if lines[i][j] == 'S' {
				r = i
				c = j
				break coorLoop
			}
		}
	}

	switch {
	case r > 0 && strings.ContainsRune("|7F", rune(lines[r-1][c])):
		dir = north
	case r < len(lines)-1 && strings.ContainsRune("|LJ", rune(lines[r+1][c])):
		dir = south
	case c > 0 && strings.ContainsRune("-LF", rune(lines[r][c-1])):
		dir = west
	default:
		dir = east
	}
	return coor{r, c, dir}
}
