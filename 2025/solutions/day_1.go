// Package solutions contains solutions of all day of 2025.
package solutions

import (
	"fmt"
	"strconv"
	"strings"
)

const Day1TEST = `L68
L30
R48
L5
R60
L55
L1
L99
R14
L82`

func Day1Part2(input string) {
	dial := 50
	pwd := 0

	for line := range strings.Lines(input) {
		line = strings.TrimSpace(line)
		direction := line[0]
		value, err := strconv.Atoi(line[1:])
		if err != nil {
			continue
		}

		base := dial

		switch direction {
		case 'R':
			dial += value
		case 'L':
			dial -= value
		}

		if dial < 0 {
			pwd -= (dial/100 - 1)
			if base == 0 {
				pwd--
			}
		} else if dial == 0 {
			pwd++
		} else if dial >= 100 {
			pwd += dial / 100
		}

		dial = (dial%100 + 100) % 100
	}

	fmt.Printf("Password: %d", pwd)
}
