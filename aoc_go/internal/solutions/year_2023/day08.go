package year2023

import (
	"strconv"
	"strings"

	"github.paxmix.aoc/internal/utils"
)

type Day08 struct{}

func init() {
	utils.Registry[8] = Day08{}
}

func (d Day08) Part1(input string) string {
	instructions, nodeStrs, _ := strings.Cut(input, "\n\n")
	nodes := make(map[string][2]string)
	for nodeStr := range strings.SplitSeq(nodeStrs, "\n") {
		name := nodeStr[:3]
		left := nodeStr[7:10]
		right := nodeStr[12:15]
		nodes[name] = [2]string{left, right}
	}
	var i int
	length := len(instructions)
	curr := "AAA"
	var step int
	for curr != "ZZZ" {
		switch instructions[i] {
		case 'L':
			curr = nodes[curr][0]
		case 'R':
			curr = nodes[curr][1]
		}
		i = (i + 1) % length
		step += 1
	}
	return strconv.Itoa(step)
}

func (d Day08) Part2(input string) string {
	instructions, nodeStrs, _ := strings.Cut(input, "\n\n")
	nodes := make(map[string][2]string)
	var startingNodes []string
	for nodeStr := range strings.SplitSeq(nodeStrs, "\n") {
		name := nodeStr[:3]
		left := nodeStr[7:10]
		right := nodeStr[12:15]
		nodes[name] = [2]string{left, right}
		if strings.HasSuffix(name, "A") {
			startingNodes = append(startingNodes, name)
		}
	}

	length := len(instructions)
	var steps []int
	for _, node := range startingNodes {
		var step int
		var i int
		for !strings.HasSuffix(node, "Z") {
			switch instructions[i] {
			case 'L':
				node = nodes[node][0]
			case 'R':
				node = nodes[node][1]
			}
			i = (i + 1) % length
			step += 1
		}
		steps = append(steps, step)
	}

	total := utils.FoldL(steps, 1, func(acc int, step int) int {
		return lcm(acc, step)
	})

	return strconv.Itoa(total)
}

func gcd(a, b int) int {
	for b != 0 {
		a %= b
		a, b = b, a
	}
	return a
}

func lcm(a, b int) int {
	return a * b / gcd(a, b)
}
