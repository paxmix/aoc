package solutions

import (
	"fmt"
	"strconv"
	"strings"
)

type Day2 struct{}

func (d Day2) Part1(input string) string {
	sum := sumInvalidIDs(input, func(id int) bool {
		length := lenInt(id)
		return length%2 == 0 && !isFactorValid(id, 2, length)
	})

	return strconv.Itoa(sum)
}

func (d Day2) Part2(input string) string {
	sum := sumInvalidIDs(input, func(id int) bool {
		return !isValidID(id)
	})

	return strconv.Itoa(sum)
}

func sumInvalidIDs(input string, isNotValid func(int) bool) int {
	invalidSum := 0

	for id := range strings.SplitSeq(input, ",") {
		pair := strings.Split(id, "-")
		min, _ := strconv.Atoi(pair[0])
		max, _ := strconv.Atoi(pair[1])

		for id := min; id <= max; id++ {
			if isNotValid(id) {
				fmt.Printf("%d is not a valid id\n", id)
				invalidSum += id
			}
		}
	}

	return invalidSum
}

func isFactorValid(ida, factor, length int) bool {
	factorTo10 := pow10(length / factor)
	id := ida
	base := id % factorTo10
	id /= factorTo10
	for id > 0 {
		if base != id%factorTo10 {
			return true
		}
		id /= factorTo10
	}
	return false
}

func isValidID(id int) bool {
	length := lenInt(id)

	for factor := 2; factor <= length; factor++ {
		if length%factor == 0 && !isFactorValid(id, factor, length) {
			return false
		}
	}

	return true
}

func lenInt(num int) int {
	if num == 0 {
		return 1
	}
	length := 0
	for num > 0 {
		length++
		num /= 10
	}
	return length
}

func pow10(factor int) int {
	pow := 1
	for range factor {
		pow *= 10
	}
	return pow
}
