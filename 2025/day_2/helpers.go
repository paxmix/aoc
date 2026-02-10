// Package day2: You get inside and take the elevator to its only other stop: the gift shop. "Thank you for visiting the North Pole!" gleefully exclaims a nearby sign. You aren't sure who is even allowed to visit the North Pole, but you know you can access the lobby through here, and from there you can access the rest of the North Pole base.
// As you make your way through the surprisingly extensive selection, one of the clerks recognizes you and asks for your help.
// As it turns out, one of the younger Elves was playing on a gift shop computer and managed to add a whole bunch of invalid product IDs to their gift shop database! Surely, it would be no trouble for you to identify the invalid product IDs for them, right?
// They've even checked most of the product ID ranges already; they only have a few product ID ranges (your puzzle input) that you'll need to check.
package day2

import (
	"fmt"
	"strconv"
	"strings"
)

const TEST = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124"

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
