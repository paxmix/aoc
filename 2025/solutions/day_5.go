package solutions

import (
	"errors"
	"log"
	"slices"
	"strconv"
	"strings"
)

type Day5 struct{}

func (d Day5) Part1(input string) string {
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

	return strconv.Itoa(freshCount)
}

func (d Day5) Part2(input string) string {
	ranges, err := parseRanges(strings.Split(input, "\n\n")[0])
	if err != nil {
		log.Fatal("errors while parsing ranges sequence")
	}
	var freshSum int
	for _, pair := range ranges {
		freshSum += (pair.max - pair.min + 1)
	}

	return strconv.Itoa(freshSum)
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
