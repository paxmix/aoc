// Package day1: You arrive at the secret entrance to the North Pole base ready to start decorating. Unfortunately, the password seems to have been changed, so you can't get in. A document taped to the wall helpfully explains:
// "Due to new security protocols, the password is locked in the safe below. Please see the attached document for the new combination."
// The safe has a dial with only an arrow on it; around the dial are the numbers 0 through 99 in order. As you turn the dial, it makes a small click noise as it reaches each number.
// The attached document (your puzzle input) contains a sequence of rotations, one per line, which tell you how to open the safe. A rotation starts with an L or R which indicates whether the rotation should be to the left (toward lower numbers) or to the right (toward higher numbers). Then, the rotation has a distance value which indicates how many clicks the dial should be rotated in that direction.
package day1

import (
	"fmt"
	"strconv"
	"strings"
)

const TEST = `L68
L30
R48
L5
R60
L55
L1
L99
R14
L82`

func Part1(input string) {
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
