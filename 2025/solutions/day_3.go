package solutions

import (
	"fmt"
	"strconv"
	"strings"
)

type Day3 struct{}

func (d Day3) Part1(input string) string {
	total := sumMaxJoltage(input, 2)
	return strconv.Itoa(total)
}

func (d Day3) Part2(input string) string {
	total := sumMaxJoltage(input, 12)
	return strconv.Itoa(total)
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
