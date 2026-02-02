// Package day3: You descend a short staircase, enter the surprisingly vast lobby, and are quickly cleared by the security checkpoint. When you get to the main elevators, however, you discover that each one has a red light above it: they're all offline.
// "Sorry about that," an Elf apologizes as she tinkers with a nearby control panel. "Some kind of electrical surge seems to have fried them. I'll try to get them online soon."
// You explain your need to get further underground. "Well, you could at least take the escalator down to the printing department, not that you'd get much further than that without the elevators working. That is, you could if the escalator weren't also offline."
// "But, don't worry! It's not fried; it just needs power. Maybe you can get it running while I keep working on the elevators."
// There are batteries nearby that can supply emergency power to the escalator for just such an occasion. The batteries are each labeled with their joltage rating, a value from 1 to 9.
package day3

import (
	"fmt"
	"strings"
)

const (
	joltageLen = 12
	TEST       = `987654321111111
811111111111119
234234234234278
818181911112111`
)

func Part1(input string) {
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

func Part2(input string) {
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
