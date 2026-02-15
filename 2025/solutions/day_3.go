package solutions

import (
	"fmt"
	"strings"
)

const (
	Day3TEST = `987654321111111
811111111111119
234234234234278
818181911112111`
)

func Day3Part1(input string) {
	total := sumMaxJoltage(input, 2)

	fmt.Printf("Part 1 total output joltage is: %d", total)
}

func Day3Part2(input string) {
	total := sumMaxJoltage(input, 12)
	fmt.Printf("Part 2 total output joltage is: %d", total)
}

func sumMaxJoltage(input string, length int) int {
	var total int

	for bank := range strings.Lines(input) {
		bank = strings.TrimSpace(bank)
		maxJoltages := make([]byte, length)
		var top int
		bankLen := len(bank)
		for i := range bank {
			battery := bank[i]
			remaining := bankLen - i
			for top > 0 &&
				maxJoltages[top-1] < battery &&
				top+remaining > length {
				top--
			}
			if top < length {
				maxJoltages[top] = battery
				top++
			}
		}

		joltage := 0
		for i := range maxJoltages {
			joltage = joltage*10 + int(maxJoltages[i]-'0')
		}

		fmt.Printf("Maximum joltage of %s is %d\n", bank, joltage)
		total += joltage
	}

	return total
}
