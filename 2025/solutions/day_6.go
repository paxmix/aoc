package solutions

import (
	"log"
	"strconv"
	"strings"
)

const Day6TEST string = `123 328  51 64 
 45 64  387 23 
  6 98  215 314
*   +   *   +  `

type Day6 struct{}

func (d Day6) Part1(input string) string {
	lines := strings.Split(input, "\n")
	ops := strings.Fields(lines[len(lines)-1])
	data := lines[:len(lines)-1]

	numOfCols := len(ops)
	result := make([]int, numOfCols)
	for i := range result {
		if ops[i] == "*" {
			result[i] = 1
		}
	}

	for _, line := range data {
		for j, val := range strings.Fields(line) {
			num, err := strconv.Atoi(val)
			if err != nil {
				log.Fatalf("Error parsing %s", val)
			}
			switch ops[j] {
			case "+":
				result[j] += num
			case "*":
				result[j] *= num
			}
		}
	}

	var total int
	for _, r := range result {
		total += r
	}

	return strconv.Itoa(total)
}

func (d Day6) Part2(input string) string {
	return ""
}
