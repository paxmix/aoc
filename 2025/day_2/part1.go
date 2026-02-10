package day2

import (
	"fmt"
)

func Part1(input string) {
	sum := sumInvalidIDs(input, func(id int) bool {
		length := lenInt(id)
		return length%2 == 0 && !isFactorValid(id, 2, length)
	})

	fmt.Printf("Sum of invalid ids: %d", sum)
}
