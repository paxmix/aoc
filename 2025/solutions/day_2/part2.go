package day2

import (
	"fmt"
)

func Part2(input string) {
	sum := sumInvalidIDs(input, func(id int) bool {
		return !isValidID(id)
	})

	fmt.Printf("Sum of invalid ids: %d", sum)
}
