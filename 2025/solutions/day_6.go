package solutions

import (
	"fmt"
	"log"
	"strconv"
	"strings"
	"time"
)

const Day6TEST string = `123 328  51 64 
 45 64  387 23 
  6 98  215 314
*   +   *   +  `

func Day6Part1(input string) {
	curTime := time.Now()
	lines := strings.Split(input, "\n")
	ops := strings.Fields(lines[len(lines)-1])
	data := lines[:len(lines)-1]

	numOfCols := len(ops)
	sum := make([]int, numOfCols)
	prod := make([]int, numOfCols)
	for i := range prod {
		prod[i] = 1
	}

	var total int

	for _, line := range data {
		for j, val := range strings.Fields(line) {
			num, err := strconv.Atoi(val)
			if err != nil {
				log.Fatalf("Error parsing %s", val)
			}
			sum[j] += num
			prod[j] *= num
		}
	}
	for i := range ops {
		switch ops[i] {
		case "+":
			total += sum[i]
		case "*":
			total += prod[i]
		}
	}
	fmt.Printf("Part 1 sum of all problems is %d - took %s", total, time.Since(curTime))
}

func Day6Part2(input string) {}
