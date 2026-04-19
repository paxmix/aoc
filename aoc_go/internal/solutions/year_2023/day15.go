package year2023

import (
	"slices"
	"strconv"
	"strings"

	"github.paxmix.aoc/internal/utils"
)

type Day15 struct{}

func init() {
	utils.Registry[15] = Day15{}
}

func (d Day15) Part1(input string) string {
	var total int
	for step := range strings.SplitSeq(input, ",") {
		total += hash(step)
	}
	return strconv.Itoa(total)
}

func (d Day15) Part2(input string) string {
	// basically make a map[lense]int with hash(label string) as the hasher
	boxes := make([][]lense, 256)
	for step := range strings.SplitSeq(input, ",") {
		if label, val, ok := strings.Cut(step, "="); ok {
			focal, _ := strconv.Atoi(val)
			boxIdx := hash(label)
			if lenseIdx := lenseIndex(boxes[boxIdx], label); lenseIdx != -1 {
				boxes[boxIdx][lenseIdx].focal = focal // change focal if lense already existed
			} else {
				boxes[boxIdx] = append(boxes[boxIdx], lense{label, focal}) // add lense to the end if not
			}
		} else if label, _, ok := strings.Cut(step, "-"); ok {
			boxIdx := hash(label)
			// delete lense if existed
			if lenseIdx := lenseIndex(boxes[boxIdx], label); lenseIdx != -1 {
				boxes[boxIdx] = append(boxes[boxIdx][:lenseIdx], boxes[boxIdx][lenseIdx+1:]...)
			}
		}
	}

	var total int
	for i, box := range boxes {
		for j, l := range box {
			total += (i + 1) * (j + 1) * l.focal
		}
	}

	return strconv.Itoa(total)
}

func hash(s string) int {
	var val int
	for i := range s {
		val += int(s[i])
		val *= 17
		val %= 256
	}
	return val
}

type lense struct {
	label string
	focal int
}

func lenseIndex(box []lense, label string) int {
	return slices.IndexFunc(box, func(l lense) bool {
		return l.label == label
	})
}
