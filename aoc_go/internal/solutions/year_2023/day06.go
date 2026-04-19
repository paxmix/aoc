package year2023

import (
	"math"
	"strconv"
	"strings"

	"github.paxmix.aoc/internal/utils"
)

type Day06 struct{}

func init() {
	utils.Registry[6] = Day06{}
}

func (d Day06) Part1(input string) string {
	// Time:      7  15   30
	// Distance:  9  40  200
	parts := strings.SplitN(input, "\n", 2)
	parseLine := func(line string) []float64 {
		fields := strings.Fields(strings.TrimSpace(strings.SplitN(line, ":", 2)[1]))
		nums := make([]float64, 0, len(fields))
		for _, num := range fields {
			if val, err := strconv.ParseFloat(num, 64); err == nil {
				nums = append(nums, val)
			}
		}
		return nums
	}
	times := parseLine(parts[0])
	dists := parseLine(parts[1])

	total := 1
	for i := range times {
		total *= possibleWays(times[i], dists[i])
	}

	return strconv.Itoa(total)
}

func (d Day06) Part2(input string) string {
	parts := strings.SplitN(input, "\n", 2)
	parseLine := func(line string) float64 {
		_, nums, _ := strings.Cut(line, ":")
		val, _ := strconv.ParseFloat(strings.ReplaceAll(nums, " ", ""), 64)
		return val
	}
	time := parseLine(parts[0])
	dist := parseLine(parts[1])

	return strconv.Itoa(possibleWays(time, dist))
}

func possibleWays(time, dist float64) int {
	// basically (t - x) * x > d => x^2 - t*x + d < 0
	// => (x-t/2)^2 < -d + t^2/4 => -sqrt(-d+t^2/4) + t/2 < x < sqrt(-d+t^2/4) + t/2
	// => need calculate (t+-sqrt(t^2+4d))/2
	discriminant := time*time - 4*dist
	if discriminant <= 0 {
		return 0 // discriminant check probably not necessary for AOC
	}
	dSqrt := math.Sqrt(discriminant)
	xMax := math.Ceil((time+dSqrt)/2 - 1)
	xMin := math.Floor((time-dSqrt)/2 + 1)
	return int(xMax - xMin + 1)
}
