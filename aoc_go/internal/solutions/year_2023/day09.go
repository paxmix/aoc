package year2023

import (
	"slices"
	"strconv"
	"strings"

	"github.paxmix.aoc/internal/utils"
)

type Day09 struct{}

func init() {
	utils.Registry[9] = Day09{}
}

func (d Day09) Part1(input string) string {
	var total int
	for line := range strings.SplitSeq(input, "\n") {
		var nextLast int
		numsStr := strings.Fields(line)
		nums := make([]int, len(numsStr))
		for i := range numsStr {
			nums[i], _ = strconv.Atoi(numsStr[i])
		}

		for slices.IndexFunc(nums, func(n int) bool { return n != 0 }) != -1 {
			nextLast += nums[len(nums)-1]

			next := make([]int, len(nums)-1)
			for i := range len(nums) - 1 {
				next[i] = nums[i+1] - nums[i]
			}
			nums = next
		}

		total += nextLast
	}
	return strconv.Itoa(total)
}

func (d Day09) Part2(input string) string {
	var total int
	for line := range strings.SplitSeq(input, "\n") {
		numsStr := strings.Fields(line)
		nums := make([]int, len(numsStr))
		for i := range numsStr {
			nums[i], _ = strconv.Atoi(numsStr[i])
		}

		var firstNums []int
		for slices.IndexFunc(nums, func(n int) bool { return n != 0 }) != -1 {
			firstNums = append(firstNums, nums[0])

			next := make([]int, len(nums)-1)
			for i := range len(nums) - 1 {
				next[i] = nums[i+1] - nums[i]
			}
			nums = next
		}

		total += utils.FoldR(firstNums, 0, func(acc, num int) int {
			return num - acc
		})
	}
	return strconv.Itoa(total)
}
