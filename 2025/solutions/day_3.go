package solutions

import (
	"fmt"
	"strings"
)

const (
	joltageLen = 12
	Day3TEST   = `987654321111111
811111111111119
234234234234278
818181911112111`
)

func Day3Part1(input string) {
	var total int

	for bank := range strings.Lines(input) {
		bank = strings.TrimSpace(bank)
		var left, right byte

		for i := 0; i < len(bank); i++ {
			battery := bank[i]
			if i != len(bank)-1 && battery > left {
				left = battery
				right = bank[i+1]
				continue
			}
			if battery > right {
				right = battery
			}
		}
		joltage := (int(left-'0')*10 + int(right-'0'))
		fmt.Printf("Maximum joltage of %s is %d\n", bank, joltage)
		total += joltage
	}

	fmt.Printf("Part 1 total output joltage is: %d", total)
}

func Day3Part2(input string) {
	var total int

	for bank := range strings.Lines(input) {
		maxJoltages := make([]byte, joltageLen)
		bank = strings.TrimSpace(bank)

		for i := range bank {
			var minCheck int
			if len(bank)-i < joltageLen {
				minCheck = joltageLen - (len(bank) - i)
			}
			maxCheck := min(i+1, joltageLen)

			for j := minCheck; j < maxCheck; j++ {
				if maxJoltages[j] < bank[i] {
					maxJoltages[j] = bank[i]
					for z := 1; z < joltageLen-j; z++ {
						maxJoltages[j+z] = '0'
					}
					break
				}
			}
		}

		joltage := 0
		for i := range maxJoltages {
			joltage = joltage*10 + int(maxJoltages[i]-'0')
		}

		fmt.Printf("Maximum joltage of %s is %d\n", bank, joltage)
		total += joltage
	}

	fmt.Printf("Part 2 total output joltage is: %d", total)
}
