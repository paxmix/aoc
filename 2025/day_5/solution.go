// Package day5: As the forklifts break through the wall, the Elves are delighted to discover that there was a cafeteria on the other side after all.
// You can hear a commotion coming from the kitchen. "At this rate, we won't have any time left to put the wreaths up in the dining hall!" Resolute in your quest, you investigate.
// "If only we hadn't switched to the new inventory management system right before Christmas!" another Elf exclaims. You ask what's going on.
// The Elves in the kitchen explain the situation: because of their complicated new inventory management system, they can't figure out which of their ingredients are fresh and which are spoiled. When you ask how it works, they give you a copy of their database (your puzzle input).
// The database operates on ingredient IDs. It consists of a list of fresh ingredient ID ranges, a blank line, and a list of available ingredient IDs.
package day5

import (
	"errors"
	"fmt"
	"log"
	"slices"
	"strconv"
	"strings"
)

const TEST string = `3-5
10-14
16-20
12-18

1
5
8
11
17
32`

func Part1(input string) {
	pair := strings.Split(input, "\n\n")
	if len(pair) != 2 {
		log.Fatal("invalid input format")
	}
	first, second := pair[0], pair[1]
	ranges, err := parseRanges(first)
	if err != nil {
		log.Fatal("errors while parsing ranges sequence")
	}
	vals, err := parseVals(second)
	if err != nil {
		log.Fatal("error while parsing values sequence")
	}

	var freshCount int
	for _, val := range vals {
		for _, pair := range ranges {
			if val >= pair.min && val <= pair.max {
				freshCount++
				break
			}
		}
	}

	fmt.Printf("Part 1 number of fresh ingredient is: %d", freshCount)
}

func Part2(input string) {
	ranges, err := parseRanges(strings.Split(input, "\n\n")[0])
	if err != nil {
		log.Fatal("errors while parsing ranges sequence")
	}
	var freshSum int
	for _, pair := range ranges {
		freshSum += (pair.max - pair.min + 1)
	}
	fmt.Printf("Part 2 number of considered fresh ingredient is %d", freshSum)
}

type Pair struct {
	min, max int
}

func parseRanges(list string) ([]Pair, error) {
	lines := strings.Split(list, "\n")
	ranges := make([]Pair, len(lines))
	for i := range lines {
		pair := strings.Split(lines[i], "-")
		if len(pair) != 2 {
			return nil, errors.New("invalid format")
		}
		low, err := strconv.Atoi(pair[0])
		if err != nil {
			return nil, err
		}
		high, err := strconv.Atoi(pair[1])
		if err != nil {
			return nil, err
		}
		ranges[i] = Pair{low, high}
	}
	return mergeRanges(ranges), nil
}

func mergeRanges(ranges []Pair) []Pair {
	merged := make([]Pair, 0, len(ranges))
	slices.SortFunc(ranges, func(a, b Pair) int {
		if a.min == b.min {
			return a.max - b.max
		} else {
			return a.min - b.min
		}
	})

	for _, pair := range ranges {
		if len(merged) == 0 || pair.min > merged[len(merged)-1].max+1 {
			merged = append(merged, pair)
		} else if pair.max > merged[len(merged)-1].max {
			merged[len(merged)-1].max = pair.max
		}
	}

	return merged
}

func parseVals(list string) ([]int, error) {
	lines := strings.Split(list, "\n")
	vals := make([]int, len(lines))
	for i := range lines {
		val, err := strconv.Atoi(lines[i])
		if err != nil {
			return nil, err
		}
		vals[i] = val
	}
	return vals, nil
}
