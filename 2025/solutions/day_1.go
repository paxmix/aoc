// Package solutions contains solutions of all day of 2025.
package solutions

import (
	"strconv"
	"strings"
)

type Day1 struct{}

func (d Day1) Part1(input string) string {
	dial := 50
	pwd := 0

	for line := range strings.Lines(input) {
		line = strings.TrimSpace(line)
		direction := line[0]
		value, err := strconv.Atoi(line[1:])
		if err != nil {
			continue
		}
		switch direction {
		case 'R':
			dial += value
		case 'L':
			dial -= value
		}
		dial = (dial + 100) % 100
		if dial == 0 {
			pwd++
		}
	}

	return strconv.Itoa(pwd)
}

func (d Day1) Part2(input string) string {
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

	return strconv.Itoa(pwd)
}
