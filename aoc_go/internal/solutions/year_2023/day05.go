package year2023

import (
	"iter"
	"slices"
	"strconv"
	"strings"

	"github.paxmix.aoc/internal/utils"
)

type Day05 struct{}

func init() {
	utils.Registry[5] = Day05{}
}

func (d Day05) Part1(input string) string {
	parts := strings.Split(input, "\n\n")
	var seeds []int
	for seedStr := range strings.FieldsSeq(strings.SplitN(parts[0], ":", 2)[1]) {
		seed, _ := strconv.Atoi(seedStr)
		seeds = append(seeds, seed)
	}

	var almanac [][]mapping
	for _, convMap := range parts[1:] {
		var cMap []mapping
		for _, convMapping := range strings.Split(convMap, "\n")[1:] {
			convField := strings.Fields(convMapping)
			destStart, _ := strconv.Atoi(convField[0])
			srcStart, _ := strconv.Atoi(convField[1])
			srcLen, _ := strconv.Atoi(convField[2])
			cMap = append(cMap, mapping{destStart, srcStart, srcStart + srcLen})
		}
		almanac = append(almanac, cMap)
	}

	for i := range seeds {
		for _, cMap := range almanac {
			for _, convMap := range cMap {
				if seeds[i] >= convMap.srcStart && seeds[i] < convMap.srcEnd {
					seeds[i] = convMap.destStart + (seeds[i] - convMap.srcStart)
					break
				}
			}
		}
	}

	minDest := seeds[0]
	for _, val := range seeds[1:] {
		if val < minDest {
			minDest = val
		}
	}

	return strconv.Itoa(minDest)
}

func (d Day05) Part2(input string) string {
	parts := strings.Split(input, "\n\n")

	var currentRanges []seedRange
	pull, stop := iter.Pull(strings.FieldsSeq(strings.SplitN(parts[0], ":", 2)[1]))
	for {
		startStr, ok1 := pull()
		lenStr, ok2 := pull()
		if !ok1 || !ok2 {
			break
		}
		start, _ := strconv.Atoi(startStr)
		length, _ := strconv.Atoi(lenStr)
		currentRanges = append(currentRanges, seedRange{start, start + length})
	}
	stop()
	currentRanges = mergeRanges(currentRanges)

	for _, convMap := range parts[1:] {
		var processedRanges []seedRange
		toProcessed := currentRanges
		for _, convMapping := range strings.Split(convMap, "\n")[1:] {
			var processNext []seedRange

			convField := strings.Fields(convMapping)
			destStart, _ := strconv.Atoi(convField[0])
			srcStart, _ := strconv.Atoi(convField[1])
			srcLen, _ := strconv.Atoi(convField[2])

			for len(toProcessed) > 0 {
				// Pop back the range that have not been processed
				r := toProcessed[len(toProcessed)-1]
				toProcessed = toProcessed[:len(toProcessed)-1]

				overlapStart := max(r.start, srcStart)
				overlapEnd := min(r.end, srcStart+srcLen)

				if overlapStart < overlapEnd {
					// Add new range altered by mapping rule
					processedRanges = append(processedRanges, seedRange{
						start: overlapStart - srcStart + destStart,
						end:   overlapEnd - srcStart + destStart,
					})

					// Add part that are not inside this mapping to process later
					if overlapStart > r.start {
						processNext = append(processNext, seedRange{
							start: r.start,
							end:   overlapStart,
						})
					}
					if overlapEnd < r.end {
						processNext = append(processNext, seedRange{
							start: overlapEnd,
							end:   r.end,
						})
					}
				} else {
					// if entirely not in the mapping rule, add to process later
					processNext = append(processNext, r)
				}
			}
			toProcessed = processNext
		}
		processedRanges = append(processedRanges, toProcessed...)
		currentRanges = mergeRanges(processedRanges)
	}

	minDest := currentRanges[0].start
	for _, seeds := range currentRanges[1:] {
		if seeds.start < minDest {
			minDest = seeds.start
		}
	}
	return strconv.Itoa(minDest)
}

type mapping struct {
	destStart, srcStart, srcEnd int
}

type seedRange struct {
	start, end int
}

func mergeRanges(seedRanges []seedRange) []seedRange {
	slices.SortFunc(seedRanges, func(a, b seedRange) int {
		return a.start - b.start
	})
	var merged []seedRange
	current := seedRanges[0]

	for _, next := range seedRanges[1:] {
		if current.end >= next.start {
			current.end = max(current.end, next.end)
		} else {
			merged = append(merged, current)
			current = next
		}
	}
	merged = append(merged, current)
	return merged
}
