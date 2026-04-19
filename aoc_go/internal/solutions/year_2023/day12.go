package year2023

import (
	"strconv"
	"strings"

	"github.paxmix.aoc/internal/utils"
)

type Day12 struct{}

func init() {
	utils.Registry[12] = Day12{}
}

func (d Day12) Part1(input string) string {
	var total int
	for line := range strings.SplitSeq(input, "\n") {
		parts := strings.SplitN(line, " ", 2)
		record := parts[0]
		var groups []int
		for group := range strings.SplitSeq(parts[1], ",") {
			val, _ := strconv.Atoi(group)
			groups = append(groups, val)
		}
		cache := make(Cache, len(record)*len(groups))
		total += solveRecursive(record, groups, cache)
	}
	return strconv.Itoa(total)
}

func (d Day12) Part2(input string) string {
	var total int
	for line := range strings.SplitSeq(input, "\n") {
		parts := strings.SplitN(line, " ", 2)

		recordDup := make([]string, 5)
		for i := range 5 {
			recordDup[i] = parts[0]
		}
		record := strings.Join(recordDup, "?")

		var baseGroups []int
		for group := range strings.SplitSeq(parts[1], ",") {
			val, _ := strconv.Atoi(group)
			baseGroups = append(baseGroups, val)
		}
		groups := make([]int, 0, 5*len(baseGroups))
		for range 5 {
			groups = append(groups, baseGroups...)
		}

		cache := make(Cache, len(record)*len(groups))
		total += solveRecursive(record, groups, cache)
	}
	return strconv.Itoa(total)
}

type Cache map[[2]int]int

func solveRecursive(record string, groups []int, cache Cache) int {
	// Check cache using the current indices of the slices
	key := [2]int{len(record), len(groups)}
	if val, ok := cache[key]; ok {
		return val
	}
	// Base Case: No more groups to find
	if len(groups) == 0 {
		if strings.Contains(record, "#") {
			return 0
		}
		return 1
	}
	// Base Case: Record is empty but we still have groups
	if len(record) == 0 {
		return 0
	}

	var count int
	first := record[0]
	// Branch 1: Treat as Operational ('.')
	// We do this if the char is '.' or '?'
	if first == '.' || first == '?' {
		count += solveRecursive(record[1:], groups, cache)
	}
	// Branch 2: Treat as Damaged ('#')
	// We do this if the char is '#' or '?'
	if first == '#' || first == '?' {
		groupSize := groups[0]
		// Check if a group of 'group_size' can start here
		// Not followed by '#'
		if groupSize <= len(record) &&
			!strings.Contains(record[:groupSize], ".") &&
			(groupSize == len(record) || record[groupSize] != '#') {
			// If valid, jump past this group and the required separator (total group_size + 1)
			nextIdx := min(groupSize+1, len(record))
			count += solveRecursive(record[nextIdx:], groups[1:], cache)
		}
	}

	cache[key] = count
	return count
}
