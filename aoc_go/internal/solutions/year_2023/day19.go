package year2023

import (
	"strconv"
	"strings"

	"github.paxmix.aoc/internal/utils"
)

type Day19 struct{}

func init() {
	utils.Registry[19] = Day19{}
}

func (d Day19) Part1(input string) string {
	system := strings.Split(input, "\n\n")
	workflows := make(map[string][]rule)
	for line := range strings.SplitSeq(system[0], "\n") {
		var rules []rule
		name, rulesStr, _ := strings.Cut(line, "{")
		for ruleStr := range strings.SplitSeq(rulesStr[:len(rulesStr)-1], ",") {
			if strings.ContainsAny(ruleStr, "<>") {
				j := strings.Index(ruleStr, ":")
				val, _ := strconv.Atoi(ruleStr[2:j])
				rules = append(rules, rule{
					category: ruleStr[0],
					op:       ruleStr[1],
					val:      val,
					target:   ruleStr[j+1:],
				})
			} else {
				rules = append(rules, rule{target: ruleStr})
			}
		}
		workflows[name] = rules
	}
	var total int
	for part := range strings.SplitSeq(system[1], "\n") {
		ratings := make(map[byte]int)
		for valPart := range strings.SplitSeq(part[1:len(part)-1], ",") {
			cat, valStr, _ := strings.Cut(valPart, "=")
			val, _ := strconv.Atoi(valStr)
			ratings[cat[0]] = val
		}

		current := "in"
		for current != "A" && current != "R" {
			rules := workflows[current]
			for _, r := range rules {
				if r.op == 0 {
					current = r.target
					break
				}
				val := ratings[r.category]
				if (r.op == '<' && val < r.val) || (r.op == '>' && val > r.val) {
					current = r.target
					break
				}
			}
		}

		if current == "A" {
			for _, v := range ratings {
				total += v
			}
		}
	}
	return strconv.Itoa(total)
}

func (d Day19) Part2(input string) string {
	return ""
}

type rule struct {
	category byte
	op       byte
	val      int
	target   string
}
