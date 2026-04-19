// Package year2023 stores AOC 2023 solutions
package year2023

import (
	"strconv"
	"strings"

	"github.paxmix.aoc/internal/utils"
)

type Day01 struct{}

func init() {
	utils.Registry[1] = Day01{}
}

func (d Day01) Part1(input string) string {
	sum := 0
	for line := range strings.SplitSeq(input, "\n") {
		var first, last int
		for i := range len(line) {
			if line[i] >= '0' && line[i] <= '9' {
				first = int(line[i] - '0')
				break
			}
		}
		for i := len(line) - 1; i >= 0; i-- {
			if line[i] >= '0' && line[i] <= '9' {
				last = int(line[i] - '0')
				break
			}
		}
		if first != 0 && last != 0 {
			sum += first*10 + last
		}
	}
	return strconv.Itoa(sum)
}

func (d Day01) Part2(input string) string {
	sum := 0
	for line := range strings.SplitSeq(input, "\n") {
		sum += getCalibrationValue(line)
	}
	return strconv.Itoa(sum)
}

var NUMS = []string{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}

func getCalibrationValue(line string) int {
	var first, last int
	found := false
	for i := range len(line) {
		if val, ok := getDigitAt(line, i); ok {
			first = val
			found = true
			break
		}
	}
	if !found {
		return 0
	}
	for i := len(line) - 1; i >= 0; i-- {
		if val, ok := getDigitAt(line, i); ok {
			last = val
			break
		}
	}
	return first*10 + last
}

func getDigitAt(line string, i int) (int, bool) {
	if line[i] >= '0' && line[i] <= '9' {
		return int(line[i] - '0'), true
	}
	for val, num := range NUMS {
		if strings.HasPrefix(line[i:], num) {
			return val + 1, true
		}
	}
	return 0, false
}
