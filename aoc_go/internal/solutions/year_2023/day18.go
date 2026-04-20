package year2023

import (
	"strconv"
	"strings"

	"github.paxmix.aoc/internal/utils"
)

type Day18 struct{}

func init() {
	utils.Registry[18] = Day18{}
}

func (d Day18) Part1(input string) string {
	var r, c int
	var perimeter int
	var area int
	for line := range strings.SplitSeq(input, "\n") {
		parts := strings.SplitN(line, " ", 3)
		step, _ := strconv.Atoi(parts[1])

		perimeter += step

		// Shoelace formula for area
		next_r, next_c := r, c
		switch parts[0] {
		case "R":
			next_c += step
		case "L":
			next_c -= step
		case "D":
			next_r += step
		case "U":
			next_r -= step
		}
		area += r*next_c - c*next_r

		r, c = next_r, next_c
	}
	if area < 0 {
		area = -area
	}
	area /= 2
	// Total lava = perimeter(outside) + interior_points(inside)
	// Use Pick's theorem area = interior_points + boundary_points(perimeter)/2 - 1
	lavaCount := area + (perimeter / 2) + 1
	return strconv.Itoa(lavaCount)
}

func (d Day18) Part2(input string) string {
	var r, c int64
	var perimeter int64
	var area int64
	for line := range strings.SplitSeq(input, "\n") {
		hexCode := strings.Fields(line)[2][2:8]
		step, _ := strconv.ParseInt(hexCode[:5], 16, 64)
		dir := hexCode[5]

		perimeter += step

		// Shoelace formula for area
		next_r, next_c := r, c
		switch dir {
		case '0':
			next_c += step
		case '1':
			next_r += step
		case '2':
			next_c -= step
		case '3':
			next_r -= step
		}
		area += r*next_c - c*next_r

		r, c = next_r, next_c
	}
	if area < 0 {
		area = -area
	}
	lavaCount := area/2 + (perimeter / 2) + 1
	return strconv.FormatInt(lavaCount, 10)
}
